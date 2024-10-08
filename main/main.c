#include "includes.h"
#include "wifi_code.h"
#include "TCP.h"

#define LED_GPIO 20


static void configure_led(void) {
    gpio_reset_pin(LED_GPIO); // Reset the GPIO pin
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); // Set the GPIO as output
    gpio_set_level(LED_GPIO, 0); // Start with LED off
}

void reciever(void *pvParameters){
    char buffer[124];
    struct sockaddr_in server_address;

    while(1){
        int sock = socket_create(TCP_SOCKET);
        if(sock < 0){
            ESP_LOGE("reciever", "Failed to create socket");
            close(sock);
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }
        setup_address(&server_address, NULL, DEVICE_PORT);

        socket_bind(sock, &server_address, NULL);

        while(1){
            
           int len = recv(sock, buffer, sizeof(buffer) -1,0);
              if(len < 0){
                ESP_LOGE("reciever", "Failed to recieve data");
                close(sock);
                vTaskDelay(pdMS_TO_TICKS(1000));
                break;
            }
            buffer[len] = '\0';
            printf("Data recieved: %s\n", buffer); 
            vTaskDelay(pdMS_TO_TICKS(1000));
            if (strcmp(buffer, "PING") == 0){
                gpio_set_level(LED_GPIO, 1);
                vTaskDelay(pdMS_TO_TICKS(5000));
                gpio_set_level(LED_GPIO, 0);
            
            }
        }
      
    }

}

void sender(void *pvParameters){
    char buffer [124];

   
}




void app_main(void) {
    // Your application co
    wifi_init_sta();


    
    
    
}

