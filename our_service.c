
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "our_service.h"
#include "ble_srv_common.h"
#include "app_error.h"

void ble_our_service_on_ble_evt(ble_os_t * p_our_service, ble_evt_t * p_ble_evt)
{
    // OUR_JOB: Step 3.D Implement switch case handling BLE events related to our service. 
}

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
static uint32_t our_char_add(ble_os_t * p_our_service)
{
    uint32_t            err_code;
		ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
		ble_uuid_t          char_uuid[NUM_OF_CHAR];
		
		ble_gatts_char_md_t char_md[NUM_OF_CHAR];
		memset(&char_md, 0, sizeof(char_md));
		
		ble_gatts_attr_md_t cccd_md[NUM_OF_CHAR];
		memset(&cccd_md, 0, sizeof(cccd_md));
	
		ble_gatts_attr_md_t attr_md[NUM_OF_CHAR];
		memset(&attr_md, 0, sizeof(attr_md));
	
		ble_gatts_attr_t    attr_char_value[NUM_OF_CHAR];
		memset(&attr_char_value, 0, sizeof(attr_char_value));
	
	for(int i=0;i<NUM_OF_CHAR;i++){
		char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid[i].type);
		APP_ERROR_CHECK(err_code);
		attr_md[i].vloc        = BLE_GATTS_VLOC_STACK;
		
		if(i<9)
			char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID+i;
		else if(i>=9)
			char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID+i+6;
		
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid[i].type);
		APP_ERROR_CHECK(err_code);
		
		if(i!=3 && i!=4 && i!=10 && i!=11){
			char_md[i].char_props.write = 1;
			BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md[i].write_perm);
		}
		if(i!=1 && i!=2 && i!=5 && i!=7 && i!=8 && i!=9){
			char_md[i].char_props.read = 1;
			BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md[i].read_perm);
		}
		
		attr_char_value[i].p_uuid      = &char_uuid[i];
		attr_char_value[i].p_attr_md   = &attr_md[i];
	}
	
	/*char init values*/
	attr_char_value[0].max_len     = 16;
	attr_char_value[0].init_len    = 16;
	uint8_t value0[16]            = {0xe2,0xc5,0x6d,0xb5,0xdf,0xfb,0x48,0xd2,0xb0,0x60,0xd0,0xf5,0xa7,0x10,0x96,0xe0};
	attr_char_value[0].p_value     = value0;	
	
	attr_char_value[1].max_len     = 2;
	attr_char_value[1].init_len    = 2;
	uint8_t value1[2]            = {0xF0,0x0D};
	attr_char_value[1].p_value     = value1;
	
	attr_char_value[2].max_len     = 2;
	attr_char_value[2].init_len    = 2;
	uint8_t value2[2]            = {0xbe,0xef};
	attr_char_value[2].p_value     = value2;
	
	attr_char_value[3].max_len     = 2;
	attr_char_value[3].init_len    = 2;
	uint8_t value3[1]            = {0xB3};
	attr_char_value[3].p_value     = value3;
	
	attr_char_value[4].max_len     = 30;
	attr_char_value[4].init_len    = 30;
	uint8_t value4[30]            = {0x02,0x01, APP_BEACON_FLAGS,0x1A,0xFF,APP_COMPANY_IDENTIFIER,0x00,APP_DEVICE_TYPE,APP_BEACON_UUID,
																			APP_MAJOR_VALUE,APP_MINOR_VALUE, 0xB3};
	attr_char_value[4].p_value     = value4;
	
	attr_char_value[5].max_len     = 4;
	attr_char_value[5].init_len    = 4;
	uint8_t value5[4]            = {0x06,0x40,0x0c,0x80};
	attr_char_value[5].p_value     = value5;																				
																			
	attr_char_value[6].max_len     = 16;
	attr_char_value[6].init_len    = 4;
	uint8_t value6[4]            = {0x12,0xc3,0x15,0x00};
	attr_char_value[6].p_value     = value6;
	
	attr_char_value[7].max_len     = 1;
	attr_char_value[7].init_len    = 1;
	uint8_t value7[1]            = {0xB3};
	attr_char_value[7].p_value     = value7;
	
	attr_char_value[8].max_len     = 10;
	attr_char_value[8].init_len    = 10;
	uint8_t value8[10]            = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	attr_char_value[8].p_value     = value8;
	
	attr_char_value[9].max_len     = 10;
	attr_char_value[9].init_len    = 10;
	uint8_t value9[1]            = {0X00};
	attr_char_value[9].p_value     = value9;
	
	attr_char_value[10].max_len     = 1;
	attr_char_value[10].init_len    = 1;
	uint8_t value10[1]            = {0x00};
	attr_char_value[10].p_value     = value10;
	
	attr_char_value[11].max_len     = 1;
	attr_char_value[11].init_len    = 1;
	uint8_t value11[1]            = {APP_DEVICE_TYPE};
	attr_char_value[11].p_value     = value11;
	
	/*adding chars to service*/
  for(int i=0;i<NUM_OF_CHAR;i++){
		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md[i],
                                   &attr_char_value[i],
                                   &p_our_service->char_handles);
		APP_ERROR_CHECK(err_code);
	}
	
    return NRF_SUCCESS;
}


/**@brief Function for initiating our new service.
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
void our_service_init(ble_os_t * p_our_service)
{
    uint32_t   err_code; 

    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_OUR_BASE_UUID;
    service_uuid.uuid = BLE_UUID_OUR_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    p_our_service->conn_handle = BLE_CONN_HANDLE_INVALID;
		//add service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &p_our_service->service_handle);
    
    APP_ERROR_CHECK(err_code);
    our_char_add(p_our_service);
}

void our_termperature_characteristic_update(ble_os_t *p_our_service, int32_t *temperature_value)
{
    // OUR_JOB: Step 3.E, Update characteristic value

}
