/* This file was generated by plugin 'Nordic Semiconductor nRF5x v.1.2.2' (BDS version 1.0.2116.0) */

#include "ble_read_write_service.h"
#include <string.h>
#include "nordic_common.h"
#include "ble_srv_common.h"
#include "app_util.h"
#include "app_util_bds.h"

#define OPCODE_LENGTH 1 /**< Length of opcode inside Read Write Service packet. */
#define HANDLE_LENGTH 2 /**< Length of handle inside Read Write Service packet. */

/* TODO Consider changing the max values if encoded data for characteristic/descriptor is fixed length */ 
#define MAX_READ_LEN (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH) /**< Maximum size of a transmitted Read. */ 
#define MAX_WRITE_LEN (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH) /**< Maximum size of a transmitted Write. */ 
#define MAX_WWR_LEN (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH) /**< Maximum size of a transmitted WwR. */ 
#define MAX_NOTIFY_LEN (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH) /**< Maximum size of a transmitted Notify. */ 
#define MAX_INDICATE_LEN (BLE_L2CAP_MTU_DEF - OPCODE_LENGTH - HANDLE_LENGTH) /**< Maximum size of a transmitted Indicate. */ 

/**@brief Function for encoding Read.
 *
 * @param[in]   p_read              Read characteristic structure to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t read_encode(ble_read_write_service_read_t * p_read, uint8_t * encoded_buffer)
{
    uint8_t len = 0; 
    len += bds_uint8_array_encode(&p_read->data, &encoded_buffer[len]); 
    return len;
}

/**@brief Function for encoding Write.
 *
 * @param[in]   p_write              Write characteristic structure to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t write_encode(ble_read_write_service_write_t * p_write, uint8_t * encoded_buffer)
{
    uint8_t len = 0; 
    len += bds_uint8_array_encode(&p_write->data, &encoded_buffer[len]); 
    return len;
}

/**@brief Function for decoding Write.
 *
 * @param[in]   data_len              Length of the field to be decoded.
 * @param[in]   p_data                Buffer where the encoded data is stored.
 * @param[out]  p_write_val           Decoded data.
 *
 * @return      Length of the decoded field.
 */
static uint8_t write_decode(uint8_t data_len, uint8_t * p_data, ble_read_write_service_write_t * p_write_val)
{
    uint8_t pos = 0;
    pos += bds_uint8_array_decode((data_len-pos), &p_data[pos], &p_write_val->data); 

    return pos;
} 
/**@brief Function for encoding WwR.
 *
 * @param[in]   p_wwr              WwR characteristic structure to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t wwr_encode(ble_read_write_service_wwr_t * p_wwr, uint8_t * encoded_buffer)
{
    uint8_t len = 0; 
    len += bds_uint8_array_encode(&p_wwr->data, &encoded_buffer[len]); 
    return len;
}

/**@brief Function for decoding WwR.
 *
 * @param[in]   data_len              Length of the field to be decoded.
 * @param[in]   p_data                Buffer where the encoded data is stored.
 * @param[out]  p_write_val           Decoded data.
 *
 * @return      Length of the decoded field.
 */
static uint8_t wwr_decode(uint8_t data_len, uint8_t * p_data, ble_read_write_service_wwr_t * p_write_val)
{
    uint8_t pos = 0;
    pos += bds_uint8_array_decode((data_len-pos), &p_data[pos], &p_write_val->data); 

    return pos;
} 
/**@brief Function for encoding Notify.
 *
 * @param[in]   p_notify              Notify characteristic structure to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t notify_encode(ble_read_write_service_notify_t * p_notify, uint8_t * encoded_buffer)
{
    uint8_t len = 0; 
    len += bds_uint8_array_encode(&p_notify->data, &encoded_buffer[len]); 
    return len;
}

/**@brief Function for encoding Indicate.
 *
 * @param[in]   p_indicate              Indicate characteristic structure to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t indicate_encode(ble_read_write_service_indicate_t * p_indicate, uint8_t * encoded_buffer)
{
    uint8_t len = 0; 
    len += bds_uint8_array_encode(&p_indicate->data, &encoded_buffer[len]); 
    return len;
}


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_read_write_service       Read Write Service Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_read_write_service_t * p_read_write_service, ble_evt_t * p_ble_evt)
{
    p_read_write_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_read_write_service       Read Write Service Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_read_write_service_t * p_read_write_service, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_read_write_service->conn_handle = BLE_CONN_HANDLE_INVALID;
}

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_read_write_service       Read Write Service Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_read_write_service_t * p_read_write_service, ble_gatts_evt_write_t * p_ble_evt)
{
    
    if(p_ble_evt->handle == p_read_write_service->write_handles.value_handle)
    {
        if(p_read_write_service->evt_handler != NULL)
        {
            ble_read_write_service_evt_t evt;
            evt.evt_type = BLE_READ_WRITE_SERVICE_WRITE_EVT_WRITE;
            write_decode(p_ble_evt->len, p_ble_evt->data, &evt.params.write);
            p_read_write_service->evt_handler(p_read_write_service, &evt);
        }
    }
    if(p_ble_evt->handle == p_read_write_service->wwr_handles.value_handle)
    {
        if(p_read_write_service->evt_handler != NULL)
        {
            ble_read_write_service_evt_t evt;
            evt.evt_type = BLE_READ_WRITE_SERVICE_WWR_EVT_WRITE;
            wwr_decode(p_ble_evt->len, p_ble_evt->data, &evt.params.wwr);
            p_read_write_service->evt_handler(p_read_write_service, &evt);
        }
    }
    if(p_ble_evt->handle == p_read_write_service->notify_handles.cccd_handle)
    {
        if(p_read_write_service->evt_handler != NULL)
        {
            ble_read_write_service_evt_t evt;
            evt.evt_type = BLE_READ_WRITE_SERVICE_NOTIFY_EVT_CCCD_WRITE;
            bds_uint16_decode(p_ble_evt->len, p_ble_evt->data, &evt.params.cccd_value);
            p_read_write_service->evt_handler(p_read_write_service, &evt);
        }
    } 
    if(p_ble_evt->handle == p_read_write_service->indicate_handles.cccd_handle)
    {
        if(p_read_write_service->evt_handler != NULL)
        {
            ble_read_write_service_evt_t evt;
            evt.evt_type = BLE_READ_WRITE_SERVICE_INDICATE_EVT_CCCD_WRITE;
            bds_uint16_decode(p_ble_evt->len, p_ble_evt->data, &evt.params.cccd_value);
            p_read_write_service->evt_handler(p_read_write_service, &evt);
        }
    } 
}

/**@brief Authorize WRITE request event handler.
 *
 * @details Handles WRITE events from the BLE stack.
 *
 * @param[in]   p_read_write_service       Read Write Service Service structure.
 * @param[in]   p_gatts_evt  GATTS Event received from the BLE stack.
 *
 */
static void on_rw_authorize_request(ble_read_write_service_t * p_read_write_service, ble_gatts_evt_t * p_gatts_evt)
{
    ble_gatts_evt_rw_authorize_request_t * p_auth_req = &p_gatts_evt->params.authorize_request;
    if (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (   (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_PREP_WRITE_REQ)
            && (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
            && (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)
           )
        {
        
            if (p_auth_req->request.write.handle == p_read_write_service->write_handles.value_handle)
            {
                on_write(p_read_write_service, &p_auth_req->request.write);
            }
        }
    }
}

/**@brief Function for handling BLE events.
 *
 * @param[in]   p_read_write_service       Read Write Service Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_read_write_service_on_ble_evt(ble_read_write_service_t * p_read_write_service, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_read_write_service, p_ble_evt);
            break;
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_read_write_service, p_ble_evt);
            break;
        case BLE_GATTS_EVT_WRITE:
            on_write(p_read_write_service, &p_ble_evt->evt.gatts_evt.params.write);
            break;
         case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_request(p_read_write_service, &p_ble_evt->evt.gatts_evt);
            break;
        default:
            //No implementation needed.
            break;
    }
}

/**@brief Function for initializing the Read Write Service. */
uint32_t ble_read_write_service_init(ble_read_write_service_t * p_read_write_service, const ble_read_write_service_init_t * p_read_write_service_init)
{
    uint32_t err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_read_write_service->evt_handler = p_read_write_service_init->evt_handler;
    p_read_write_service->conn_handle = BLE_CONN_HANDLE_INVALID;
    
    // Add a custom base UUID.
    ble_uuid128_t bds_base_uuid = {{0x9A, 0x6F, 0xB4, 0x56, 0x37, 0x77, 0x93, 0x8F, 0xB3, 0x47, 0xB8, 0xD7, 0x00, 0x00, 0xB8, 0xB7}};
    uint8_t       uuid_type;
    err_code = sd_ble_uuid_vs_add(&bds_base_uuid, &uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    ble_uuid.type = uuid_type;
    ble_uuid.uuid = 0x51C6;
        
    // Add service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_read_write_service->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    // Add Read characteristic
    ble_read_write_service_read_t read_initial_value = p_read_write_service_init->ble_read_write_service_read_initial_value; 

    uint8_t read_encoded_value[MAX_READ_LEN];
    ble_add_char_params_t add_read_params;
    memset(&add_read_params, 0, sizeof(add_read_params));
    
    add_read_params.uuid                = 0x0010;
    add_read_params.uuid_type           = ble_uuid.type; 
    add_read_params.max_len             = MAX_READ_LEN;
    add_read_params.init_len            = read_encode(&read_initial_value, read_encoded_value);
    add_read_params.p_init_value        = read_encoded_value; 
    add_read_params.char_props.read     = 1; 
    add_read_params.read_access         = SEC_OPEN; 
    // 1 for variable length and 0 for fixed length.
    add_read_params.is_var_len          = 1; 

    err_code = characteristic_add(p_read_write_service->service_handle, &add_read_params, &(p_read_write_service->read_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    // Add Write characteristic
    ble_read_write_service_write_t write_initial_value = p_read_write_service_init->ble_read_write_service_write_initial_value; 

    uint8_t write_encoded_value[MAX_WRITE_LEN];
    ble_add_char_params_t add_write_params;
    memset(&add_write_params, 0, sizeof(add_write_params));
    
    add_write_params.uuid                = 0x0011;
    add_write_params.uuid_type           = ble_uuid.type; 
    add_write_params.max_len             = MAX_WRITE_LEN;
    add_write_params.init_len            = write_encode(&write_initial_value, write_encoded_value);
    add_write_params.p_init_value        = write_encoded_value; 
    add_write_params.char_props.write    = 1; 
    add_write_params.write_access        = SEC_OPEN; 
    // 1 for variable length and 0 for fixed length.
    add_write_params.is_var_len          = 1; 

    err_code = characteristic_add(p_read_write_service->service_handle, &add_write_params, &(p_read_write_service->write_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    // Add WwR characteristic
    ble_read_write_service_wwr_t wwr_initial_value = p_read_write_service_init->ble_read_write_service_wwr_initial_value; 

    uint8_t wwr_encoded_value[MAX_WWR_LEN];
    ble_add_char_params_t add_wwr_params;
    memset(&add_wwr_params, 0, sizeof(add_wwr_params));
    
    add_wwr_params.uuid                = 0x0012;
    add_wwr_params.uuid_type           = ble_uuid.type; 
    add_wwr_params.max_len             = MAX_WWR_LEN;
    add_wwr_params.init_len            = wwr_encode(&wwr_initial_value, wwr_encoded_value);
    add_wwr_params.p_init_value        = wwr_encoded_value; 
    add_wwr_params.char_props.write_wo_resp    = 1; 
    add_wwr_params.write_access        = SEC_OPEN; 
    // 1 for variable length and 0 for fixed length.
    add_wwr_params.is_var_len          = 1; 

    err_code = characteristic_add(p_read_write_service->service_handle, &add_wwr_params, &(p_read_write_service->wwr_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    // Add Notify characteristic
    ble_read_write_service_notify_t notify_initial_value = p_read_write_service_init->ble_read_write_service_notify_initial_value; 

    uint8_t notify_encoded_value[MAX_NOTIFY_LEN];
    ble_add_char_params_t add_notify_params;
    memset(&add_notify_params, 0, sizeof(add_notify_params));
    
    add_notify_params.uuid                = 0x0013;
    add_notify_params.uuid_type           = ble_uuid.type; 
    add_notify_params.max_len             = MAX_NOTIFY_LEN;
    add_notify_params.init_len            = notify_encode(&notify_initial_value, notify_encoded_value);
    add_notify_params.p_init_value        = notify_encoded_value; 
    add_notify_params.char_props.notify   = 1; 
    add_notify_params.char_props.read     = 1; 
    add_notify_params.read_access         = SEC_OPEN; 
    add_notify_params.cccd_write_access   = SEC_OPEN;
    // 1 for variable length and 0 for fixed length.
    add_notify_params.is_var_len          = 1; 

    err_code = characteristic_add(p_read_write_service->service_handle, &add_notify_params, &(p_read_write_service->notify_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    // Add Indicate characteristic
    ble_read_write_service_indicate_t indicate_initial_value = p_read_write_service_init->ble_read_write_service_indicate_initial_value; 

    uint8_t indicate_encoded_value[MAX_INDICATE_LEN];
    ble_add_char_params_t add_indicate_params;
    memset(&add_indicate_params, 0, sizeof(add_indicate_params));
    
    add_indicate_params.uuid                = 0x0014;
    add_indicate_params.uuid_type           = ble_uuid.type; 
    add_indicate_params.max_len             = MAX_INDICATE_LEN;
    add_indicate_params.init_len            = indicate_encode(&indicate_initial_value, indicate_encoded_value);
    add_indicate_params.p_init_value        = indicate_encoded_value; 
    add_indicate_params.char_props.indicate = 1; 
    add_indicate_params.char_props.read     = 1; 
    add_indicate_params.read_access         = SEC_OPEN; 
    add_indicate_params.cccd_write_access   = SEC_OPEN;
    // 1 for variable length and 0 for fixed length.
    add_indicate_params.is_var_len          = 1; 

    err_code = characteristic_add(p_read_write_service->service_handle, &add_indicate_params, &(p_read_write_service->indicate_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    } 

    return NRF_SUCCESS;
}

/**@brief Function for setting the Read. */
uint32_t ble_read_write_service_read_set(ble_read_write_service_t * p_read_write_service, ble_read_write_service_read_t * p_read)
{
    ble_gatts_value_t gatts_value;
    uint8_t encoded_value[MAX_READ_LEN];

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = read_encode(p_read, encoded_value);
    gatts_value.offset  = 0;
    gatts_value.p_value = encoded_value;

    return sd_ble_gatts_value_set(p_read_write_service->conn_handle, p_read_write_service->read_handles.value_handle, &gatts_value);
}

/**@brief Function for setting the Notify. */
uint32_t ble_read_write_service_notify_set(ble_read_write_service_t * p_read_write_service, ble_read_write_service_notify_t * p_notify)
{
    ble_gatts_value_t gatts_value;
    uint8_t encoded_value[MAX_NOTIFY_LEN];

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = notify_encode(p_notify, encoded_value);
    gatts_value.offset  = 0;
    gatts_value.p_value = encoded_value;

    return sd_ble_gatts_value_set(p_read_write_service->conn_handle, p_read_write_service->notify_handles.value_handle, &gatts_value);
}

/**@brief Function for sending the Notify. */
uint32_t ble_read_write_service_notify_send(ble_read_write_service_t * p_read_write_service, ble_read_write_service_notify_t * p_notify)
{
    uint32_t err_code = NRF_SUCCESS;

    if (p_read_write_service->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        ble_gatts_hvx_params_t hvx_params;
        uint8_t encoded_value[MAX_NOTIFY_LEN];
        uint16_t hvx_len;

        // Initialize value struct.
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_len           = notify_encode(p_notify, encoded_value);
        hvx_params.handle = p_read_write_service->notify_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.p_len  = &hvx_len;
        hvx_params.offset = 0;
        hvx_params.p_data = encoded_value;

        err_code = sd_ble_gatts_hvx(p_read_write_service->conn_handle, &hvx_params);
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}

/**@brief Function for setting the Indicate. */
uint32_t ble_read_write_service_indicate_set(ble_read_write_service_t * p_read_write_service, ble_read_write_service_indicate_t * p_indicate)
{
    ble_gatts_value_t gatts_value;
    uint8_t encoded_value[MAX_INDICATE_LEN];

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = indicate_encode(p_indicate, encoded_value);
    gatts_value.offset  = 0;
    gatts_value.p_value = encoded_value;

    return sd_ble_gatts_value_set(p_read_write_service->conn_handle, p_read_write_service->indicate_handles.value_handle, &gatts_value);
}

/**@brief Function for sending the Indicate. */
uint32_t ble_read_write_service_indicate_send(ble_read_write_service_t * p_read_write_service, ble_read_write_service_indicate_t * p_indicate)
{
    uint32_t err_code = NRF_SUCCESS;

    if (p_read_write_service->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        ble_gatts_hvx_params_t hvx_params;
        uint8_t encoded_value[MAX_INDICATE_LEN];
        uint16_t hvx_len;

        // Initialize value struct.
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_len           = indicate_encode(p_indicate, encoded_value);
        hvx_params.handle = p_read_write_service->indicate_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_INDICATION;
        hvx_params.p_len  = &hvx_len;
        hvx_params.offset = 0;
        hvx_params.p_data = encoded_value;

        err_code = sd_ble_gatts_hvx(p_read_write_service->conn_handle, &hvx_params);
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}

