// Compile and flash with:  mbed compile -f
// Target: K64F
// Toolchain: GCC_ARM

// mbed libs:
#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"
#include "EthernetInterface.h"
#include "TCPServer.h"
#include "TCPSocket.h"

// My libs:
#include "RGBLED.h"
#include "Color.h"
#include "Joystick.h"
#include "Buzzer.h"
#include "Potentiometer.h"
#include "client.h"
#include "server.h"
#include "UI.h"
#include "Frame.h"

// Unique static IP given for each mbed
#define IP                          "192.168.0.108"
#define GATEWAY                     "192.168.0.1"
#define MASK                        "255.255.255.0"
#define TCP_PORT                    4000
#define MAX_PENDING                 1

// Gui settings
#define DARK_THEME                  true

// Shield IO
#define I2C_SDA                     D14
#define I2C_SCL                     D15
#define BUZZER                      D6
#define RGB_LED_BLUE                D7
#define RGB_LED_GREEN               D9
#define RGB_LED_RED                 D5
#define POT_1                       A0
#define POT_2                       A1
#define JOYSTICK_RIGHT              A5
#define JOYSTICK_UP                 A2
#define JOYSTICK_CENTER             D4
#define JOYSTICK_LEFT               A4
#define JOYSTICK_DOWN               A3
#define LCD_NCS                     D10
#define LCD_A0                      D7
#define LCD_SCK                     D13
#define LCD_RESET                   D12
#define LCD_MOSI                    D11

// Initialisations
C12832 lcd(LCD_MOSI, LCD_SCK, LCD_RESET, LCD_A0, LCD_NCS);
UI ui(&lcd);
LM75B temp_sensor(I2C_SDA, I2C_SCL);
RGBLED rgb_led(RGB_LED_RED, RGB_LED_GREEN, RGB_LED_BLUE);
Joystick joystick(JOYSTICK_UP, JOYSTICK_DOWN, JOYSTICK_LEFT, JOYSTICK_RIGHT, JOYSTICK_CENTER);
Buzzer buzzer(BUZZER);
Potentiometer pot1(POT_1);
EthernetInterface eth;

// PROGRAM vars
volatile bool receiving = false;
char next_hop_ip[15];
volatile float temp;

 
// ! NOT USED DUE TO mbed-os V5 PIN ROUTING ERRORS !

// RGB LED Thread
// void rgbCycler()    
// {
//     Color *color;
//     color = new Color();
//     rgb_led.setColor(color);
//     float progress = 0.0f;
//     while(true) {
//         rgb_led.cycleRGB(progress);
//         ThisThread::sleep_for(20);
//         progress+= 0.01f;
//     }
// }

// Client thread, used for UI and packet sending
void clientThread() {
    while(true){
        ui.promptNextHop(&joystick, next_hop_ip);
        printf("\n\rSending to: %s\n\r", next_hop_ip);
        ui.title("Sending new frame!");

        // Making next frame
        char data[256];
        Frame frame(data);
        frame.len = 12;
        frame.idd = 109;                                    // TODO: Extract ID from IP
        frame.tmp = temp_sensor.read()/0.125f;
        frame.pwm = pot1.value * 255;
        frame.tun = 1;
        frame.id[0] = 109;                                  // TODO: Extract ID from IP
        frame.generate(data);
        
        // Send next frame
        Client client(&eth);
        client.send(next_hop_ip, TCP_PORT, data);
        ThisThread::sleep_for(100);
    }
}

void serverUI(){
    ui.title("Received a frame!");
    ui.alert();
    ui.temperature("Temperature: %.3f°C", temp);
    ThisThread::sleep_for(2000);
    ui.title("Sending next frame!");
}

// Main Thread
int main() {
    // Setup UI
    ui.darkTheme(DARK_THEME);
    ui.title("mbed-round-robin");
    ThisThread::sleep_for(1000);

    // Configure ethernet interface
    ui.title("Connecting ethernet");
    eth.disconnect();
    eth.set_network(IP,MASK,GATEWAY);
    eth.connect();
    printf("Ip address: %s\n\r", eth.get_ip_address());

    // Initialize server
    ui.title("Setting up server");
    Server server(&eth, TCP_PORT);

    // Initializing RGB LED
    Color *color;
    color = new Color();
    color->red = 1;
    color->green = 1;
    color->blue = 1;
    color->alfa = 0;
    rgb_led.setColor(color);

    // Main thread
    while(true) {
        // Start Client
        Thread t_client(clientThread);

        // Recieve package
        char data[256];
        memset(data, 0x0, 256);
        server.recieve(data);
        printf("\n\rReceived a frame!\n\r");       

        // Handle incomming package
        Frame frame(data);
        frame.decode();

        color->alfa = frame.pwm/255.0f;
        temp = frame.tmp*0.125f;

        // Stop client thread and give ui acces to server
        t_client.terminate();
        Thread t_server_ui(serverUI);
        rgb_led.setColor(color);
        buzzer.playNumber(frame.tun);

        // Making next frame
        frame.len++;
        frame.idd = 109;                            // TODO: Extract ID from IP
        frame.tmp = temp_sensor.read()/0.125f;
        frame.pwm = pot1.value * 255;
        frame.pwm = 255;
        // TODO: add own ID to ID list
        frame.tun++;
        frame.generate(data);

        // Send next frame
        Client client(&eth);
        client.send(next_hop_ip, TCP_PORT, data);
        
        // Wait for ui thread to finish
        t_server_ui.join();
    }
}


