
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "our_service.h"
#include "ble_srv_common.h"
#include "app_error.h"

/**@brief Function for adding our new characterstic to "Our service" that we initiated in the previous tutorial. 
 *
 * @param[in]   p_our_service        Our Service structure.
 *
 */
static uint32_t our_char_add(ble_os_t * p_our_service)
{
	
	if(jeden==0){
    uint32_t   err_code = 0; // Variable to hold return codes from library and softdevice functions
    
    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
    ble_uuid_t          char_uuid;
    ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
    char_uuid.uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
    sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
    APP_ERROR_CHECK(err_code);
    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
    char_md.char_props.read = 1;
    char_md.char_props.write = 1;

    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
    char_md.p_cccd_md           = &cccd_md;
    char_md.char_props.notify   = 1;
   
    
    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md)); 
    attr_md.vloc        = BLE_GATTS_VLOC_STACK;   
    
    
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));        
    attr_char_value.p_uuid      = &char_uuid;
    attr_char_value.p_attr_md   = &attr_md;
    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
    attr_char_value.max_len     = 4;
    attr_char_value.init_len    = 4;
    uint8_t value[4]            = {0x12,0x34,0x56,0x78};
    attr_char_value.p_value     = value;

    // OUR_JOB: Step 2.E, Add our new characteristic to the service
    err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                       &char_md,
                                       &attr_char_value,
                                       &p_our_service->char_handles);
    APP_ERROR_CHECK(err_code);
	}
	else{
		uint32_t            err_code;
		ble_uuid128_t       base_uuid = BLE_UUID_OUR_BASE_UUID;
		ble_uuid_t          char_uuid[NUM_OF_CHAR];
		
		ble_gatts_char_md_t char_md[NUM_OF_CHAR];							 /// characteristic metadata
		ble_gatts_attr_t    attr_char_value[NUM_OF_CHAR];				// characteristic value atrribute
		ble_gatts_attr_md_t attr_md[NUM_OF_CHAR];								//attribute metadata
		
	
		memset(&attr_md, 0, sizeof(attr_md));
		memset(&char_md, 0, sizeof(char_md));
		memset(&attr_char_value, 0, sizeof(attr_char_value));
		
		
		ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
		
		
	for(int i=0;i<NUM_OF_CHAR;i++){
		char_uuid[i].uuid      = BLE_UUID_OUR_CHARACTERISTC_UUID;
		err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid[i].type);
		APP_ERROR_CHECK(err_code);
		attr_md[i].vloc        = BLE_GATTS_VLOC_STACK;
		
		cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
    char_md[i].p_cccd_md           = &cccd_md;
    char_md[i].char_props.notify   = 1;
		
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
	
	// UUID
	attr_char_value[0].max_len     = 16;
	attr_char_value[0].init_len    = 16;
	uint8_t value0[16]            = {0xe2,0xc5,0x6d,0xb5,0xdf,0xfb,0x48,0xd2,0xb0,0x60,0xd0,0xf5,0xa7,0x10,0x96,0xe0};
	attr_char_value[0].p_value     = value0;	
	// MAJOR
	attr_char_value[1].max_len     = 2;
	attr_char_value[1].init_len    = 2;
	uint8_t value1[2]            = {0xF0,0x0D};
	attr_char_value[1].p_value     = value1;
	// MINOR
	attr_char_value[2].max_len     = 2;
	attr_char_value[2].init_len    = 2;
	uint8_t value2[2]            = {0xbe,0xef};
	attr_char_value[2].p_value     = value2;
	// Tx Power
	attr_char_value[3].max_len     = 2;
	attr_char_value[3].init_len    = 2;
	uint8_t value3[1]            = {0xB3};
	attr_char_value[3].p_value     = value3;
	// packet preview
	attr_char_value[4].max_len     = 30;
	attr_char_value[4].init_len    = 30;
	uint8_t value4[30]            = {0x02,0x01, APP_BEACON_FLAGS,0x1A,0xFF,APP_COMPANY_IDENTIFIER,0x00,APP_DEVICE_TYPE,APP_BEACON_UUID,
																			APP_MAJOR_VALUE,APP_MINOR_VALUE, 0xB3};
	attr_char_value[4].p_value     = value4;
	// adv params
	attr_char_value[5].max_len     = 4;
	attr_char_value[5].init_len    = 4;
	uint8_t value5[4]            = {0x06,0x40,0x0c,0x80};
	attr_char_value[5].p_value     = value5;																				
	// beacon name																			
	attr_char_value[6].max_len     = 16;
	attr_char_value[6].init_len    = 4;
	uint8_t value6[4]            = {0x12,0xc3,0x15,0x00};
	attr_char_value[6].p_value     = value6;
	//device power
	attr_char_value[7].max_len     = 1;
	attr_char_value[7].init_len    = 1;
	uint8_t value7[1]            = {0xB3};
	attr_char_value[7].p_value     = value7;
	// password
	attr_char_value[8].max_len     = BEACON_PASSWORD_LNG;
	attr_char_value[8].init_len    = BEACON_PASSWORD_LNG;
	uint8_t value8[BEACON_PASSWORD_LNG]            	 = {BEACON_PASSWORD};
	attr_char_value[8].p_value     = value8;
	// change password
	attr_char_value[9].max_len     = BEACON_PASSWORD_LNG;
	attr_char_value[9].init_len    = BEACON_PASSWORD_LNG;
	uint8_t value9[BEACON_PASSWORD_LNG] = {BEACON_PASSWORD};
	attr_char_value[9].p_value     = value9;
	// is login
	attr_char_value[10].max_len     = 1;
	attr_char_value[10].init_len    = 1;
	uint8_t value10[1]            = {0x00};
	attr_char_value[10].p_value     = value10;
	// beacon type
	attr_char_value[11].max_len     = 1;
	attr_char_value[11].init_len    = 1;
	uint8_t value11[1]            = {APP_DEVICE_TYPE};
	attr_char_value[11].p_value     = value11;
	
  for(int i=0;i<NUM_OF_CHAR;i++){
		err_code = sd_ble_gatts_characteristic_add(p_our_service->service_handle,
                                   &char_md[i],
                                   &attr_char_value[i],
                                   &p_our_service->char_handles);
		APP_ERROR_CHECK(err_code);
	}
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

void isLogin_update_value(ble_os_t *p_our_service, bool* isLogin)
{
		char pop[8];
		sprintf(pop, "%d", p_our_service->conn_handle);
		SEGGER_RTT_WriteString(0, pop);
	if(p_our_service->conn_handle != BLE_CONN_HANDLE_INVALID){
		SEGGER_RTT_WriteString(0, "\nisLoginupdateIf\n");
    uint16_t               len = 1;
		ble_gatts_hvx_params_t hvx_params;
		memset(&hvx_params, 0, sizeof(hvx_params));

		hvx_params.handle = p_our_service->char_handles.value_handle;
		
		hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
		hvx_params.offset = 0;
		hvx_params.p_len  = &len;
		hvx_params.p_data = (uint8_t*)isLogin;  

		sd_ble_gatts_hvx(p_our_service->conn_handle, &hvx_params);
	}
}
