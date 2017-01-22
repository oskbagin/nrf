
#ifndef OUR_SERVICE_H__
#define OUR_SERVICE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

#define jeden 1
#define APP_BEACON_INFO_LENGTH          0x17                              /**< Total length of information advertised by the Beacon. */
#define APP_ADV_DATA_LENGTH             0x15                              /**< Length of manufacturer specific data in the advertisement. */
#define APP_DEVICE_TYPE                 0x02                              /**< 0x02 refers to Beacon. */
#define APP_MEASURED_RSSI               0xB3                              /**< The Beacon's measured RSSI at 1 meter distance in dBm. */
#define APP_COMPANY_IDENTIFIER          0x004C                            /**< Company identifier for Nordic Semiconductor ASA. as per www.bluetooth.org. */
#define APP_MAJOR_VALUE                 0x79, 0x2E                        /**< Major value used to identify Beacons. */ 
#define APP_MINOR_VALUE                 0xFA, 0x06                        /**< Minor value used to identify Beacons. */ 
#define APP_BEACON_UUID                 0xF7, 0x82, 0x6D, 0xA6, \
                                        0x4F, 0xA2, 0x4E, 0x98, \
                                        0x80, 0x24, 0xBC, 0x5B, \
                                        0x71, 0xE0, 0x89, 0x3E            /**< Proprietary UUID for Beacon. */
#define APP_BEACON_FLAGS								0x06
#define BEACON_PASSWORD									00000000000
#define BLE_UUID_OUR_BASE_UUID              {{0x6a,0x4a, 0x22,0x05,0x77,0x08,0x79,0xa1,0x39,0x43,0xdd,0x48,0xe0,0x43,0xd3,0x12}}
#define BLE_UUID_OUR_SERVICE_UUID                0x43e0

#define BLE_UUID_OUR_CHARACTERISTC_UUID          0x43E1

#define NUM_OF_CHAR																12
// This structure contains various status information for our service. 
// The name is based on the naming convention used in Nordics SDKs. 
// 'ble’ indicates that it is a Bluetooth Low Energy relevant structure and 
// ‘os’ is short for Our Service). 
typedef struct
{
    uint16_t                    conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection).*/
    uint16_t                    service_handle; /**< Handle of Our Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t		char_handles;
}ble_os_t;

/**@brief Function for initializing our new service.
 *
 * @param[in]   p_our_service       Pointer to Our Service structure.
 */
void our_service_init(ble_os_t * p_our_service);

/**@brief Function for updating and sending new characteristic values
 *
 * @details The application calls this function whenever our timer_timeout_handler triggers
 *
 * @param[in]   p_our_service                     Our Service structure.
 * @param[in]   characteristic_value     New characteristic value.
 */
void our_termperature_characteristic_update(ble_os_t *p_our_service, int32_t *temperature_value);

#endif  /* _ OUR_SERVICE_H__ */
