#include <main.h>

extern SPI_HandleTypeDef hspi2;

uint8_t read8bit(uint8_t reg){
	uint8_t rx_data[2];
	uint8_t tx_data[2];

	tx_data[0] = reg | 0x80;
	tx_data[1] = 0x00;

	HAL_GPIO_WritePin(GPIOB,SPI2_CS_Pin,GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, tx_data, rx_data, 2, 1);
	HAL_GPIO_WritePin(GPIOB,SPI2_CS_Pin,GPIO_PIN_SET);

	return rx_data[1];

}

uint8_t who_am_i;
uint8_t acc_x;
int flag = 0;

void main_cpp(){
	__HAL_SPI_ENABLE(&hspi2);

	while(1){
		who_am_i = read8bit(0x75);

		if(who_am_i == 0x71){
			flag = 1;
		}

		acc_x = read8bit(0x43);

		HAL_Delay(60);
	}

}
