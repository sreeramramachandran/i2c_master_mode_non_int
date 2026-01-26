/*
 * i2cmaster.c
 *
 *  Created on: Jan 25, 2026
 *      Author: microairf97
 */


#include "main.h"
#include "i2cmaster.h"
#include<string.h>

extern I2C_HandleTypeDef hi2c1;
#define SIZE 30
#define SLAVE_ADD 0x12
uint8_t tx_data[SIZE];

#define RX_SIZE     8

uint8_t rx_buf[RX_SIZE];



void write_data(uint8_t *pdata,uint8_t len)
{
	tx_data[0]=len;
	memcpy(&tx_data[1],pdata,len);
	uint16_t dev_add = SLAVE_ADD<<1;
	printf("TX to 0x%02X, len=%d\r\n", dev_add>>1, tx_data[0]);
	HAL_I2C_Master_Transmit(&hi2c1, dev_add, tx_data, len+1, 1000);
}
//void read_data(uint8_t *pdata, uint8_t len)
//{
//    uint16_t dev_add = SLAVE_ADD << 1;
//
//    if (HAL_I2C_Master_Receive(&hi2c1, dev_add, rx_data, RX_SIZE, 1000) == HAL_OK)
//    {
//        memcpy(&value, &rx_data[0], 4);
//        memcpy(&timestamp, &rx_data[4], 4);
//        printf("MASTER RX → value=%ld, timestamp=%lu\r\n", value, timestamp);
//    }
//    else
//    {
//        printf("I2C READ ERROR\r\n");
//    }
//}

void read_data(void)
{
    uint16_t dev_addr = SLAVE_ADD << 1;

    if (HAL_I2C_Master_Receive(&hi2c1,
                               dev_addr,
                               rx_buf,
                               RX_SIZE,
                               1000) == HAL_OK)
    {
        int32_t value;
        uint32_t timestamp;

        memcpy(&value, &rx_buf[0], 4);
        memcpy(&timestamp, &rx_buf[4], 4);

        printf("MASTER RX → value=%ld, timestamp=%lu\r\n",
               value, timestamp);
    }
    else
    {
        printf("I2C READ ERROR\r\n");
    }
}
