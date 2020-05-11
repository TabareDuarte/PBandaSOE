//BANDA SELECCIONADORA DE OBJETOS//

////  Incluyo librerias //////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "freertos/queue.h"
#include "driver/gpio.h"


////   Sensores   /////////////////////////////////////////////////
#define sensorColor       12;
#define sensorServoBlanco 14;
#define sensorServoNegro  27;
#define botonInicio		  26;
#define botonParo         25;


////    Actuadores    //////////////////////////////////////////////
#define servoBlanco		  15;
#define servoNegro         2;
#define motorBanda         4;


////////////    Tareas del programa     //////////////////////////
void app_main()
{
    nvs_flash_init();
    xTaskCreate(&tareaInicioBanda, "IniciarBanda", 1024, NULL, 5, NULL);
    xTaskCreate(&tareaParoBanda, "PararBanda", 1024, NULL, 4, NULL);
    xTaskCreate(&tareaDetectarColor, "DetectarColor", 2048, NULL, 4, NULL);
    xTaskCreate(&tareaDetectarObjetoBlanco, "DetectarObjetoBlanco", 2048, NULL, 3, NULL);
    xTaskCreate(&tareaDetectarObjetoNegro, "DetectarObjetoNegro", 2048, NULL, 4, NULL);
    xTaskCreate(&tareaSepararObjeto, "SepararObjeto", 1024, NULL, 4, NULL);

    
////////////    Configurando salidas    ////////////////////////
  gpio_pad_select_gpio(servoBlanco);
  gpio_set_direction(servoBlanco, GPIO_MODE_OUTPUT);
  
  gpio_pad_select_gpio(servoNegro);
  gpio_set_direction(servoNegro, GPIO_MODE_OUTPUT);
  
  gpio_pad_select_gpio(motorBanda);
  gpio_set_direction(motorBanda, GPIO_MODE_OUTPUT);
    
    
    
///////////    Configurando entradas   ////////////////////////  
  gpio_pad_select_gpio(sensorColor);
  gpio_set_direction(sensorColor, GPIO_MODE_INPUT);
  gpio_set_pull_mode(sensorColor,GPIO_PULLUP_ONLY);  //Este modo está a discusión
  
  gpio_pad_select_gpio(sensorServoBlanco);
  gpio_set_direction(sensorServoBlanco, GPIO_MODE_INPUT);
  gpio_set_pull_mode(sensorServoBlanco,GPIO_PULLUP_ONLY);  //Este modo está a discusión
  
  gpio_pad_select_gpio(sensorServoNegro);
  gpio_set_direction(sensorServoNegro, GPIO_MODE_INPUT);
  gpio_set_pull_mode(sensorServoNegro,GPIO_PULLUP_ONLY);  //Este modo está a discusión
  
  vTaskSuspend( ParoB );  //Suspenso todas las tareas menos la de encendido de banda, para que sólo atienda a esta y no gaste energía en las demás
  vTaskSuspend( DetectarC );  //  pero aún falta ver si se puede emplear la sistaxis de tareas aquí, así.
  vTaskSuspend( DetectarOB );
  vTaskSuspend( DetectarON );
  vTaskSuspend( SepararO );
  
  vTaskStartScheduler(); 

}

///////// Tarea para detectar que se precionó el botón de inicio   ///////////////
void tareaInicioBanda(void *pvParameter)
{
    while(1) 
    {
		TaskHandle_t InicioB;
		
		vTaskResume( ParoB );     //Reanudo o quito la suspensión de las tareas para que inicie todo el proceso de la banda
		vTaskResume( DetectarC );
		vTaskResume( DetectarOB );
		vTaskResume( DetectarON );
		vTaskResume( SepararO );
			
		gpio_set_level(motorBanda, 1); //Pongo en uno una de las terminales del controlador o reelevador del motor de la banda
    }
    
}


///////// Tarea para detectar que se precionó el botón de paro   ///////////////
void tareaParoBanda(void *pvParameter)
{
    while(1) 
    {	
		TaskHandle_t ParoB;
			
			
		gpio_set_level(motorBanda, 0);
    }
    
}



///////   Tarea para el sensor de blanco/negro    //////////////////////
void tareaDetectarColor(void *pvParameter)
{
    while(1) 
    {
		TaskHandle_t DetectarC;

    }
    //vTaskDelete(NULL);
}


///// Tarea del sensor de proximidad para recorrer objetos blancos /////////////////
void tareaDetectarObjetoBlanco(void *pvParameter)
{
    while(1) 
    {
		TaskHandle_t DetectarOB;

    }
    //vTaskDelete(NULL);
}



///// Tarea del sensor de proximidad para recorrer objetos negros /////////////////
void tareaDetectarObjetoNegro(void *pvParameter)
{
    while(1) 
    {
		TaskHandle_t DetectarON;

    }
    //vTaskDelete(NULL);
}




///// Tarea para separar el objeto moviendo el servo correspondiente /////////////////
void tareaSepararObjeto(void *pvParameter)
{
    while(1) 
    {
		TaskHandle_t SepararO;

    }
    //vTaskDelete(NULL);
}


