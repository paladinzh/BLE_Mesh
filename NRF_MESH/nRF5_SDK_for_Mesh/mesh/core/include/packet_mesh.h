/* Copyright (c) 2010 - 2017, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PACKET_MESH_H__
#define PACKET_MESH_H__

#include <stdint.h>


#define PACKET_MESH_NET_IVI_OFFSET   (0)       /**< Offset to the net_ivi field.*/
#define PACKET_MESH_NET_IVI_MASK     (0x80)    /**< Mask for net_ivi field. */
#define PACKET_MESH_NET_IVI_MASK_INV (0x7F)    /**< Inverse mask for net_ivi field. */

#define PACKET_MESH_NET_NID_OFFSET   (0)       /**< Offset to the net_nid field.*/
#define PACKET_MESH_NET_NID_MASK     (0x7F)    /**< Mask for net_nid field. */
#define PACKET_MESH_NET_NID_MASK_INV (0x80)    /**< Inverse mask for net_nid field. */

#define PACKET_MESH_NET_CTL_OFFSET   (1)       /**< Offset to the net_ctl field.*/
#define PACKET_MESH_NET_CTL_MASK     (0x80)    /**< Mask for net_ctl field. */
#define PACKET_MESH_NET_CTL_MASK_INV (0x7F)    /**< Inverse mask for net_ctl field. */

#define PACKET_MESH_NET_TTL_OFFSET   (1)       /**< Offset to the net_ttl field.*/
#define PACKET_MESH_NET_TTL_MASK     (0x7F)    /**< Mask for net_ttl field. */
#define PACKET_MESH_NET_TTL_MASK_INV (0x80)    /**< Inverse mask for net_ttl field. */

#define PACKET_MESH_NET_SEQ0_OFFSET   (2)       /**< Offset to the net_seq field (0).*/
#define PACKET_MESH_NET_SEQ1_OFFSET   (3)       /**< Offset to the net_seq field (1).*/
#define PACKET_MESH_NET_SEQ2_OFFSET   (4)       /**< Offset to the net_seq field (2).*/

#define PACKET_MESH_NET_SRC0_OFFSET   (5)       /**< Offset to the net_src field (0).*/
#define PACKET_MESH_NET_SRC1_OFFSET   (6)       /**< Offset to the net_src field (1).*/

#define PACKET_MESH_NET_DST0_OFFSET   (7)       /**< Offset to the net_dst field (0).*/
#define PACKET_MESH_NET_DST1_OFFSET   (8)       /**< Offset to the net_dst field (1).*/

#define PACKET_MESH_TRS_CONTROL_SEGACK_OBO_OFFSET   (0)       /**< Offset to the trs_control_segack_obo field.*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_OBO_MASK     (0x80)    /**< Mask for trs_control_segack_obo field. */
#define PACKET_MESH_TRS_CONTROL_SEGACK_OBO_MASK_INV (0x7F)    /**< Inverse mask for trs_control_segack_obo field. */

#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_OFFSET   (0)       /**< Offset to the trs_control_segack_seqzero field (0).*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_OFFSET   (1)       /**< Offset to the trs_control_segack_seqzero field (1).*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_MASK     (0x7F)    /**< Mask for trs_control_segack_seqzero field (0). */
#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_MASK     (0xFC)    /**< Mask for trs_control_segack_seqzero field (1). */
#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_MASK_INV (0x80)    /**< Inverse mask for trs_control_segack_seqzero field (0). */
#define PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_MASK_INV (0x03)    /**< Inverse mask for trs_control_segack_seqzero field (1). */

#define PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK0_OFFSET   (2)       /**< Offset to the trs_control_segack_block_ack field (0).*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK1_OFFSET   (3)       /**< Offset to the trs_control_segack_block_ack field (1).*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK2_OFFSET   (4)       /**< Offset to the trs_control_segack_block_ack field (2).*/
#define PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK3_OFFSET   (5)       /**< Offset to the trs_control_segack_block_ack field (3).*/

#define PACKET_MESH_TRS_ACCESS_AKF_OFFSET   (0)       /**< Offset to the trs_access_akf field.*/
#define PACKET_MESH_TRS_ACCESS_AKF_MASK     (0x40)    /**< Mask for trs_access_akf field. */
#define PACKET_MESH_TRS_ACCESS_AKF_MASK_INV (0xBF)    /**< Inverse mask for trs_access_akf field. */

#define PACKET_MESH_TRS_ACCESS_AID_OFFSET   (0)       /**< Offset to the trs_access_aid field.*/
#define PACKET_MESH_TRS_ACCESS_AID_MASK     (0x3F)    /**< Mask for trs_access_aid field. */
#define PACKET_MESH_TRS_ACCESS_AID_MASK_INV (0xC0)    /**< Inverse mask for trs_access_aid field. */

#define PACKET_MESH_TRS_COMMON_SEG_OFFSET   (0)       /**< Offset to the trs_common_seg field.*/
#define PACKET_MESH_TRS_COMMON_SEG_MASK     (0x80)    /**< Mask for trs_common_seg field. */
#define PACKET_MESH_TRS_COMMON_SEG_MASK_INV (0x7F)    /**< Inverse mask for trs_common_seg field. */

#define PACKET_MESH_TRS_CONTROL_OPCODE_OFFSET   (0)       /**< Offset to the trs_control_opcode field.*/
#define PACKET_MESH_TRS_CONTROL_OPCODE_MASK     (0x7F)    /**< Mask for trs_control_opcode field. */
#define PACKET_MESH_TRS_CONTROL_OPCODE_MASK_INV (0x80)    /**< Inverse mask for trs_control_opcode field. */

#define PACKET_MESH_TRS_SEG_SZMIC_OFFSET   (1)       /**< Offset to the trs_seg_szmic field.*/
#define PACKET_MESH_TRS_SEG_SZMIC_MASK     (0x80)    /**< Mask for trs_seg_szmic field. */
#define PACKET_MESH_TRS_SEG_SZMIC_MASK_INV (0x7F)    /**< Inverse mask for trs_seg_szmic field. */

#define PACKET_MESH_TRS_SEG_SEQZERO0_OFFSET   (1)       /**< Offset to the trs_seg_seqzero field (0).*/
#define PACKET_MESH_TRS_SEG_SEQZERO1_OFFSET   (2)       /**< Offset to the trs_seg_seqzero field (1).*/
#define PACKET_MESH_TRS_SEG_SEQZERO0_MASK     (0x7F)    /**< Mask for trs_seg_seqzero field (0). */
#define PACKET_MESH_TRS_SEG_SEQZERO1_MASK     (0xFC)    /**< Mask for trs_seg_seqzero field (1). */
#define PACKET_MESH_TRS_SEG_SEQZERO0_MASK_INV (0x80)    /**< Inverse mask for trs_seg_seqzero field (0). */
#define PACKET_MESH_TRS_SEG_SEQZERO1_MASK_INV (0x03)    /**< Inverse mask for trs_seg_seqzero field (1). */

#define PACKET_MESH_TRS_SEG_SEGO0_OFFSET   (2)       /**< Offset to the trs_seg_sego field (0).*/
#define PACKET_MESH_TRS_SEG_SEGO1_OFFSET   (3)       /**< Offset to the trs_seg_sego field (1).*/
#define PACKET_MESH_TRS_SEG_SEGO0_MASK     (0x03)    /**< Mask for trs_seg_sego field (0). */
#define PACKET_MESH_TRS_SEG_SEGO1_MASK     (0xE0)    /**< Mask for trs_seg_sego field (1). */
#define PACKET_MESH_TRS_SEG_SEGO0_MASK_INV (0xFC)    /**< Inverse mask for trs_seg_sego field (0). */
#define PACKET_MESH_TRS_SEG_SEGO1_MASK_INV (0x1F)    /**< Inverse mask for trs_seg_sego field (1). */

#define PACKET_MESH_TRS_SEG_SEGN_OFFSET   (3)       /**< Offset to the trs_seg_segn field.*/
#define PACKET_MESH_TRS_SEG_SEGN_MASK     (0x1F)    /**< Mask for trs_seg_segn field. */
#define PACKET_MESH_TRS_SEG_SEGN_MASK_INV (0xE0)    /**< Inverse mask for trs_seg_segn field. */

#define PACKET_MESH_NET_MAX_SIZE      (29)    /**< Size of net packet. */
#define PACKET_MESH_NET_PDU_OFFSET    (9)    /**< Offset to net payload. */
#define PACKET_MESH_NET_PDU_MAX_SIZE  (20)    /**< Max PDU size for net packets. */

#define PACKET_MESH_TRS_CONTROL_SEGACK_SIZE (6)    /**< Size of trs control segack packet. */

#define PACKET_MESH_TRS_SEG_MAX_SIZE      (16)    /**< Size of trs seg packet. */
#define PACKET_MESH_TRS_SEG_PDU_OFFSET    (4)    /**< Offset to trs seg payload. */
#define PACKET_MESH_TRS_SEG_PDU_MAX_SIZE  (12)    /**< Max PDU size for trs seg packets. */

#define PACKET_MESH_TRS_UNSEG_MAX_SIZE      (16)    /**< Size of trs unseg packet. */
#define PACKET_MESH_TRS_UNSEG_PDU_OFFSET    (1)    /**< Offset to trs unseg payload. */
#define PACKET_MESH_TRS_UNSEG_PDU_MAX_SIZE  (15)    /**< Max PDU size for trs unseg packets. */

/**
 * Packet type for net packet.
 */
typedef struct
{
    uint8_t pdu[29];
} packet_mesh_net_packet_t;

/**
 * Packet type for trs control packet.
 */
typedef struct
{
    uint8_t pdu[6];
} packet_mesh_trs_control_packet_t;

/**
 * Packet type for trs packet.
 */
typedef struct
{
    uint8_t pdu[16];
} packet_mesh_trs_packet_t;

/**
 * Gets the net payload pointer.
 * @param[in,out] p_pkt Packet pointer.
 * @returns Pointer to the start of the upper transport PDU.
 */
static inline const uint8_t * packet_mesh_net_payload_get(const packet_mesh_net_packet_t * p_pkt)
{
    return &p_pkt->pdu[PACKET_MESH_NET_PDU_OFFSET];
}

/**
 * Gets the trs_seg payload pointer.
 * @param[in,out] p_pkt Packet pointer.
 * @returns Pointer to the start of the upper transport PDU.
 */
static inline const uint8_t * packet_mesh_trs_seg_payload_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return &p_pkt->pdu[PACKET_MESH_TRS_SEG_PDU_OFFSET];
}

/**
 * Gets the trs_unseg payload pointer.
 * @param[in,out] p_pkt Packet pointer.
 * @returns Pointer to the start of the upper transport PDU.
 */
static inline const uint8_t * packet_mesh_trs_unseg_payload_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return &p_pkt->pdu[PACKET_MESH_TRS_UNSEG_PDU_OFFSET];
}
/**
 * Gets the least significant bit of IV index.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the least significant bit of IV index.
 */
static inline uint8_t packet_mesh_net_ivi_get(const packet_mesh_net_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_NET_IVI_OFFSET] & PACKET_MESH_NET_IVI_MASK) > 0);
}

/**
 * Sets the least significant bit of IV index.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the least significant bit of IV index.
 */
static inline void packet_mesh_net_ivi_set(packet_mesh_net_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_IVI_OFFSET] &= PACKET_MESH_NET_IVI_MASK_INV;
    p_pkt->pdu[PACKET_MESH_NET_IVI_OFFSET] |= (val << 7) & PACKET_MESH_NET_IVI_MASK;
}

/**
 * Gets the network key identifier.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the network key identifier.
 */
static inline uint8_t packet_mesh_net_nid_get(const packet_mesh_net_packet_t * p_pkt)
{
    return (p_pkt->pdu[PACKET_MESH_NET_NID_OFFSET] & PACKET_MESH_NET_NID_MASK);
}

/**
 * Sets the network key identifier.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the network key identifier.
 */
static inline void packet_mesh_net_nid_set(packet_mesh_net_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_NID_OFFSET] &= PACKET_MESH_NET_NID_MASK_INV;
    p_pkt->pdu[PACKET_MESH_NET_NID_OFFSET] |= (val & PACKET_MESH_NET_NID_MASK);
}

/**
 * Gets the network control.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the network control.
 */
static inline uint8_t packet_mesh_net_ctl_get(const packet_mesh_net_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_NET_CTL_OFFSET] & PACKET_MESH_NET_CTL_MASK) > 0);
}

/**
 * Sets the network control.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the network control.
 */
static inline void packet_mesh_net_ctl_set(packet_mesh_net_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_CTL_OFFSET] &= PACKET_MESH_NET_CTL_MASK_INV;
    p_pkt->pdu[PACKET_MESH_NET_CTL_OFFSET] |= (val << 7) & PACKET_MESH_NET_CTL_MASK;
}

/**
 * Gets the time to live.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the time to live.
 */
static inline uint8_t packet_mesh_net_ttl_get(const packet_mesh_net_packet_t * p_pkt)
{
    return (p_pkt->pdu[PACKET_MESH_NET_TTL_OFFSET] & PACKET_MESH_NET_TTL_MASK);
}

/**
 * Sets the time to live.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the time to live.
 */
static inline void packet_mesh_net_ttl_set(packet_mesh_net_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_TTL_OFFSET] &= PACKET_MESH_NET_TTL_MASK_INV;
    p_pkt->pdu[PACKET_MESH_NET_TTL_OFFSET] |= (val & PACKET_MESH_NET_TTL_MASK);
}

/**
 * Gets the sequence number.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the sequence number.
 */
static inline uint32_t packet_mesh_net_seq_get(const packet_mesh_net_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_NET_SEQ0_OFFSET] << 16) |
            (p_pkt->pdu[PACKET_MESH_NET_SEQ1_OFFSET] << 8) |
            p_pkt->pdu[PACKET_MESH_NET_SEQ2_OFFSET]);
}

/**
 * Sets the sequence number.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the sequence number.
 */
static inline void packet_mesh_net_seq_set(packet_mesh_net_packet_t * p_pkt, uint32_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_SEQ0_OFFSET] = (val >> 16) & 0xFF;
    p_pkt->pdu[PACKET_MESH_NET_SEQ1_OFFSET] = (val >> 8) & 0xFF;
    p_pkt->pdu[PACKET_MESH_NET_SEQ2_OFFSET] = val & 0xFF;
}

/**
 * Gets the source address.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the source address.
 */
static inline uint16_t packet_mesh_net_src_get(const packet_mesh_net_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_NET_SRC0_OFFSET] << 8) |
            p_pkt->pdu[PACKET_MESH_NET_SRC1_OFFSET]);
}

/**
 * Sets the source address.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the source address.
 */
static inline void packet_mesh_net_src_set(packet_mesh_net_packet_t * p_pkt, uint16_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_SRC0_OFFSET] = (val >> 8) & 0xFF;
    p_pkt->pdu[PACKET_MESH_NET_SRC1_OFFSET] = val & 0xFF;
}

/**
 * Gets the destination address.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the destination address.
 */
static inline uint16_t packet_mesh_net_dst_get(const packet_mesh_net_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_NET_DST0_OFFSET] << 8) |
            p_pkt->pdu[PACKET_MESH_NET_DST1_OFFSET]);
}

/**
 * Sets the destination address.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the destination address.
 */
static inline void packet_mesh_net_dst_set(packet_mesh_net_packet_t * p_pkt, uint16_t val)
{
    p_pkt->pdu[PACKET_MESH_NET_DST0_OFFSET] = (val >> 8) & 0xFF;
    p_pkt->pdu[PACKET_MESH_NET_DST1_OFFSET] = val & 0xFF;
}

/**
 * Gets the 'on behalf of' flag.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the 'on behalf of' flag.
 */
static inline uint8_t packet_mesh_trs_control_segack_obo_get(const packet_mesh_trs_control_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_OBO_OFFSET] & PACKET_MESH_TRS_CONTROL_SEGACK_OBO_MASK) > 0);
}

/**
 * Sets the 'on behalf of' flag.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the 'on behalf of' flag.
 */
static inline void packet_mesh_trs_control_segack_obo_set(packet_mesh_trs_control_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_OBO_OFFSET] &= PACKET_MESH_TRS_CONTROL_SEGACK_OBO_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_OBO_OFFSET] |= (val << 7) & PACKET_MESH_TRS_CONTROL_SEGACK_OBO_MASK;
}

/**
 * Gets the least significant bits of SeqAuth.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the least significant bits of SeqAuth.
 */
static inline uint16_t packet_mesh_trs_control_segack_seqzero_get(const packet_mesh_trs_control_packet_t * p_pkt)
{
    return (((p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_OFFSET] & PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_MASK) << 6) |
            ((p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_OFFSET] & PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_MASK) >> 2));
}

/**
 * Sets the least significant bits of SeqAuth.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the least significant bits of SeqAuth.
 */
static inline void packet_mesh_trs_control_segack_seqzero_set(packet_mesh_trs_control_packet_t * p_pkt, uint16_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_OFFSET] &= PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_OFFSET] |= (val >> 6) & PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO0_MASK;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_OFFSET] &= PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_OFFSET] |= (val << 2) & PACKET_MESH_TRS_CONTROL_SEGACK_SEQZERO1_MASK;
}

/**
 * Gets the block acknowledgement field.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the block acknowledgement field.
 */
static inline uint32_t packet_mesh_trs_control_segack_block_ack_get(const packet_mesh_trs_control_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK0_OFFSET] << 24) |
            (p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK1_OFFSET] << 16) |
            (p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK2_OFFSET] << 8) |
            p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK3_OFFSET]);
}

/**
 * Sets the block acknowledgement field.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the block acknowledgement field.
 */
static inline void packet_mesh_trs_control_segack_block_ack_set(packet_mesh_trs_control_packet_t * p_pkt, uint32_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK0_OFFSET] = (val >> 24) & 0xFF;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK1_OFFSET] = (val >> 16) & 0xFF;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK2_OFFSET] = (val >> 8) & 0xFF;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_SEGACK_BLOCK_ACK3_OFFSET] = val & 0xFF;
}

/**
 * Gets the application key flag.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the application key flag.
 */
static inline uint8_t packet_mesh_trs_access_akf_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AKF_OFFSET] & PACKET_MESH_TRS_ACCESS_AKF_MASK) > 0);
}

/**
 * Sets the application key flag.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the application key flag.
 */
static inline void packet_mesh_trs_access_akf_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AKF_OFFSET] &= PACKET_MESH_TRS_ACCESS_AKF_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AKF_OFFSET] |= (val << 6) & PACKET_MESH_TRS_ACCESS_AKF_MASK;
}

/**
 * Gets the application key identifier.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the application key identifier.
 */
static inline uint8_t packet_mesh_trs_access_aid_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return (p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AID_OFFSET] & PACKET_MESH_TRS_ACCESS_AID_MASK);
}

/**
 * Sets the application key identifier.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the application key identifier.
 */
static inline void packet_mesh_trs_access_aid_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AID_OFFSET] &= PACKET_MESH_TRS_ACCESS_AID_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_ACCESS_AID_OFFSET] |= (val & PACKET_MESH_TRS_ACCESS_AID_MASK);
}

/**
 * Gets the segmentation bit.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the segmentation bit.
 */
static inline uint8_t packet_mesh_trs_common_seg_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_TRS_COMMON_SEG_OFFSET] & PACKET_MESH_TRS_COMMON_SEG_MASK) > 0);
}

/**
 * Sets the segmentation bit.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the segmentation bit.
 */
static inline void packet_mesh_trs_common_seg_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_COMMON_SEG_OFFSET] &= PACKET_MESH_TRS_COMMON_SEG_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_COMMON_SEG_OFFSET] |= (val << 7) & PACKET_MESH_TRS_COMMON_SEG_MASK;
}

/**
 * Gets the transport control opcode.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the transport control opcode.
 */
static inline uint8_t packet_mesh_trs_control_opcode_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return (p_pkt->pdu[PACKET_MESH_TRS_CONTROL_OPCODE_OFFSET] & PACKET_MESH_TRS_CONTROL_OPCODE_MASK);
}

/**
 * Sets the transport control opcode.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the transport control opcode.
 */
static inline void packet_mesh_trs_control_opcode_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_OPCODE_OFFSET] &= PACKET_MESH_TRS_CONTROL_OPCODE_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_CONTROL_OPCODE_OFFSET] |= (val & PACKET_MESH_TRS_CONTROL_OPCODE_MASK);
}

/**
 * Gets the size of MIC flag.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the size of MIC flag.
 */
static inline uint8_t packet_mesh_trs_seg_szmic_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return ((p_pkt->pdu[PACKET_MESH_TRS_SEG_SZMIC_OFFSET] & PACKET_MESH_TRS_SEG_SZMIC_MASK) > 0);
}

/**
 * Sets the size of MIC flag.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the size of MIC flag.
 */
static inline void packet_mesh_trs_seg_szmic_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SZMIC_OFFSET] &= PACKET_MESH_TRS_SEG_SZMIC_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SZMIC_OFFSET] |= (val << 7) & PACKET_MESH_TRS_SEG_SZMIC_MASK;
}

/**
 * Gets the least significant bits of SeqAuth.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the least significant bits of SeqAuth.
 */
static inline uint16_t packet_mesh_trs_seg_seqzero_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return (((p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO0_OFFSET] & PACKET_MESH_TRS_SEG_SEQZERO0_MASK) << 6) |
            ((p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO1_OFFSET] & PACKET_MESH_TRS_SEG_SEQZERO1_MASK) >> 2));
}

/**
 * Sets the least significant bits of SeqAuth.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the least significant bits of SeqAuth.
 */
static inline void packet_mesh_trs_seg_seqzero_set(packet_mesh_trs_packet_t * p_pkt, uint16_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO0_OFFSET] &= PACKET_MESH_TRS_SEG_SEQZERO0_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO0_OFFSET] |= (val >> 6) & PACKET_MESH_TRS_SEG_SEQZERO0_MASK;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO1_OFFSET] &= PACKET_MESH_TRS_SEG_SEQZERO1_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEQZERO1_OFFSET] |= (val << 2) & PACKET_MESH_TRS_SEG_SEQZERO1_MASK;
}

/**
 * Gets the segment offset number.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the segment offset number.
 */
static inline uint8_t packet_mesh_trs_seg_sego_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return (((p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO0_OFFSET] & PACKET_MESH_TRS_SEG_SEGO0_MASK) << 3) |
             (p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO1_OFFSET] & PACKET_MESH_TRS_SEG_SEGO1_MASK) >> 5);
}

/**
 * Sets the segment offset number.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the segment offset number.
 */
static inline void packet_mesh_trs_seg_sego_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO0_OFFSET] &= PACKET_MESH_TRS_SEG_SEGO0_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO0_OFFSET] |= (val >> 3) & PACKET_MESH_TRS_SEG_SEGO0_MASK;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO1_OFFSET] &= PACKET_MESH_TRS_SEG_SEGO1_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGO1_OFFSET] |= (val << 5) & PACKET_MESH_TRS_SEG_SEGO1_MASK;
}

/**
 * Gets the last segment number.
 * @param[in] p_pkt Packet pointer.
 * @returns Value of the last segment number.
 */
static inline uint8_t packet_mesh_trs_seg_segn_get(const packet_mesh_trs_packet_t * p_pkt)
{
    return (p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGN_OFFSET] & PACKET_MESH_TRS_SEG_SEGN_MASK);
}

/**
 * Sets the last segment number.
 * @param[in,out] p_pkt Packet pointer.
 * @param[in]     val   Value of the last segment number.
 */
static inline void packet_mesh_trs_seg_segn_set(packet_mesh_trs_packet_t * p_pkt, uint8_t val)
{
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGN_OFFSET] &= PACKET_MESH_TRS_SEG_SEGN_MASK_INV;
    p_pkt->pdu[PACKET_MESH_TRS_SEG_SEGN_OFFSET] |= (val & PACKET_MESH_TRS_SEG_SEGN_MASK);
}

#endif
