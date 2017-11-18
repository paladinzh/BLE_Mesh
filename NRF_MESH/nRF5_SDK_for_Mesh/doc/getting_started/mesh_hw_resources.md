# Resource usage

The mesh stack is designed to be built together with the user application and resides in the application code space. It also relies on the SoftDevice being present, and thus carries the hardware resource requirements that comes with the SoftDevice. For information on SoftDevice hardware resource requirements see the relevant SoftDevice SDS. The mesh stack requires a minimum set of the hardware resources provided by the Nordic SoCs in addition to the SoftDevice's requirements in order to be functional.

## SoftDevice Radio Timeslot API

The mesh stack operates concurrently with the SoftDevice through the SoftDevice Radio Timeslot API. The mesh stack takes complete control over the Radio Timeslot API, and this is unavailable to the application.

## Hardware peripherals
The following hardware peripherals are occupied by the mesh stack:

### QDEC
Although the quadrature decoder hardware is not used by the mesh, the interrupt request line dedicated to the QDEC module is utilized for post processing within the mesh stack. As all the software interrupts available to the application on the nRF51 are frequently used in the nRF5 SDK, the mesh stack uses the QDEC IRQ handler for processing, as this peripheral is not commonly used. This makes combining the mesh stack with SDK applications easier.

If the QDEC peripheral and its interrupt request line is needed by the application, the mesh stack can be configured to use the SWI0 IRQ by defining `BEARER_EVENT_USE_SWI0` during the build.

### RADIO
Shared with the SoftDevice, the RADIO peripheral is occupied by the mesh stack during the acquired Radio Timeslot sessions. The RADIO peripheral should not be modified by the application at any time.

### TIMER0
Shared with the SoftDevice, the TIMER0 peripheral is occupied by the mesh stack during the acquired Radio Timeslot sessions. The TIMER0 peripheral should not be modified by the application at any time.

### ECB
Shared with the SoftDevice, the ECB peripheral is occupied by the mesh stack during the acquired Radio Timeslot sessions on the nRF51. For the nRF52, the mesh stack uses the SoftDevice interface for the ECB.

### UART0
If built with serial support, the mesh stack uses the UART0 peripheral to serialize its API. The mesh stack takes full control over the peripheral, and it should not be modified by the application at any time.

## RAM and flash usage
The core mesh can be configured for achieving higher performance and functionality, or reduced footprint depending on application needs. The tables below outline the flash and minimum statically allocated RAM requirements by each module. The mesh stack shares its call stack with the application and the SoftDevice, and requires a minimum call stack size of *2KB*. The mesh stack also requires the presence of a heap (of minimum *380 bytes*) unless it is configured with a custom memory allocator to replace the need for malloc (see `transport_sar_mem_funcs_set` in the transport module).

### nRF51
| Library                              | Flash use `-Otime` | Flash Use `-Os` | Min RAM | Default RAM |
| --------                             | --------           | --------        | ------- |---          |
|   Core without Persistent Storage    | 26.7KB             | 24.3KB          | 2KB     | 6.6KB
|   Core with Persistent Storage       | 33.8KB             | 31.5KB          | 2.6KB   | 7.5KB
|   Access without Persistent Storage  | 10.7KB             | 10.1KB          | 400B    | 400B
|   Access with Persistent Storage     | 13.9KB             | 13.5KB          | 400B    | 400B
|   DFU + Bootloader                   | 27KB               | 26KB            | 1.2KB   | 1.2KB
|   Provisioning Common                | 5.0KB              | 5.7KB           | 0       | 0KB
|   Provisionee                        | 1.8KB              | 1.7KB           | 0       | 800B
|   Provisioner                        | 1.6KB              | 1.42KB          | 0       | 800B
|   Serial                             | 10KB               | 9KB             | 1.4KB   | 2KB
|   RTT                                | 3KB                | 2.3KB           | 1.3KB   | 1.3KB
|   uECC                               | 7.0KB              | 6KB             | 4Bytes  | 4Bytes
|   **Totals with Persistent Storage** | 103.8KB            | 97.12KB         | 7.1KB   | 14.0KB
Table: Flash and RAM requirements for the mesh stack libraries on nRF51 when built with ARMCC v5.

### nRF52
| Library                              | Flash use `-Otime` | Flash Use `-Os` | min RAM | Default RAM |
| --------                             | --------           | --------        | ------- |---          |
|   Core without Persistent Storage    | 24.5KB             | 21.0KB          | 2 KB    | 6.6KB
|   Core with Persistent Storage       | 33.2KB             | 26.4KB          | 2.6 KB  | 7.5KB
|   Access without Persistent Storage  | 11.5KB             | 10.1KB          | 400B    | 400B
|   Access with Persistent Storage     | 13.9KB             | 13.3KB          | 400B    | 400B
|   DFU + Bootloader                   | 25KB               | 24.7KB          | 1.2 KB  | 1.2KB
|   Provisioning Common                | 5.5KB              | 4.7KB           | 0       | 0KB
|   Provisionee                        | 1.6KB              | 1.5KB           | 0       | 800B
|   Provisioner                        | 1.6KB              | 1.44KB          | 0       | 800B
|   Serial                             | 9.3KB              | 7.5KB           | 1.4KB   | 2KB
|   RTT                                | 1.6KB              | 1.5KB           | 1.26KB  | 1.3KB
|   uECC                               | 8.8KB              | 6.2KB           | 4Bytes  | 4Bytes
|   **Totals with Persistent Storage** | 100.5KB            | 87.3KB          | 7.1KB   | 14.0KB
Table: Flash and RAM requirements for the mesh stack libraries on nRF52 when built with ARMCC v5.

## Flash lifetime
The flash hardware can withstand a limited number of write/erase cycles. As the mesh stack uses the flash to store state across power failures, the device flash will eventually start failing, resulting in unexpected behavior in the mesh stack. As explained in [the Flash Manager documentation](@ref md_doc_libraries_flash_manager), the Flash Manager will write new data to the area by allocating a new entry before invalidating the old one. Because of this the area must be erased periodically.

The mesh stack uses flash to store the following states:
- Encryption keys
- Mesh addresses
- Access model composition
- Access model configuration
- Network message sequence number
- Network IV index state
- DFU metadata

Assuming reconfiguration of keys, addresses and access configuration is rare, the most likely source of flash write exhaustion is the network states. The network message sequence number is written to flash continuously, in user-configurable blocks.

To calculate the flash lifetime of a device, some parameters must be defined:

| Name              | Description                      | Configuration parameter | Default nRF51 | Default nRF52 | Unit |
|------             |---------------                   |-------------------------|------------   | --------------|------|
| `MSG_PER_SEC`     | The number of messages created by the device every second (relayed messages not included). The message sequence number field is 24 bits, and cannot be depleted within one IV update period, which must be at least 192 hours. Because of this, a device cannot possibly send more than `2^24 / (192 * 60 * 60) = 24.3` messages per second on average, without breaking the specification. | N/A | 24.3 | 24.3 | messages/s |
| `BLOCK_SIZE`      | The message sequence numbers are allocated in blocks. Every block represents a set number of messages. | `NETWORK_SEQNUM_FLASH_BLOCK_SIZE` | 8192 | 8192 | messages |
| `ENTRY_SIZE`      | The size of a single allocated block entry in flash storage. | N/A | 8 | 8 | bytes |
| `AREA_SIZE`       | Size of the storage area. Must be in flash page sized increments. Defaults to a single page. | `NET_FLASH_PAGE_COUNT` | 1024 | 4096 | bytes |
| `AREA_OVERHEAD`   | Static overhead in the storage area, per page. | N/A | 8 | 8 | bytes |
| `ERASE_CYCLES`    | The number of times the device can erase a flash page before it starts faulting. | N/A | 20000 | 10000 | - |


The formula for network state flash exhaustion is as follows:

`FLASH LIFETIME [seconds] = ((AREA_SIZE - AREA_OVERHEAD) * ERASE_CYCLES) / (ENTRY_SIZE * MSG_PER_SEC / BLOCK_SIZE)`

### Examples

| Case   | Result   |
|--      | --       |
| Worst case nRF51, default settings | 26.97 years |
| Worst case nRF52, default settings | 54.58 years |

It is recommended to recalculate the flash lifetime for any changes to the default flash configuration, as it might cause significantly reduced product lifetime.

### Flash configuration parameters

While the default settings should be sufficient for most applications, there are tradeoffs in the flash configuration, which application developers might want to tune.

The sequence number block size will affect the number of power resets the device can do within a 192 hour IV update period. For security reasons, the device can never send a message with the same sequence number twice with an IV update period. This means that the device has to allocate a new block of sequence numbers _before_ it sends its first packet after a power reset, to avoid a scenario where it reuses the same sequence number on next power up. As a consequence, every power reset requires a sequence number block allocation, which can exhaust the sequence number space faster than accounted for in the lifetime calculations. With the default block size of 8192, the device may reset 2048 times in a 192 hour interval. If a higher rate of resets is expected, a smaller block size should be considered. Keep in mind that this will directly affect the flash lifetime, as more frequent writes are required during normal operation. The block size can also be increased if the number of power resets are expected to be lower than 2048, resulting in longer device lifetime.

The flash area size will affect the number of erases required for the configuration and network state areas, but be aware that this does not alter the device lifetime significantly, as the Flash Manager defragmentation process requires a separate backup page that will be erased once for every backed up page. Adding pages to the flash area will therefore result in fewer, but more expensive defragmentations, with effectively no change to the number of erases required.
