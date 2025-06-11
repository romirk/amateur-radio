/// AX.25 Frame Definitions

#include <stdint.h>

typedef enum [[gnu::packed]] {
  OBC = 0,
  TRX = 1,
  ANT = 2,
  EPS = 3,
  AOCS = 4,
  BITFLIP = 5
} subsystem_type;

typedef struct [[gnu::packed]] {
  /** Call sign */
  uint8_t header[16];

  /** Command Message Counter */
  uint8_t cmc;

  /** # of CMC */
  uint8_t n_cmc;

  /** Unique frame identifier */
  uint8_t frame_id;

  /** Command shall be executed after time tag. */
  uint16_t time_tag;

  /** Subsystem ID */
  subsystem_type subsystem_id;

  /**
   * Command Message ID
   *
   * Unique ID for the command
   */
  uint8_t cmid;

  /** Payload data */
  uint8_t data[177];
} frame_uplink_s;

typedef enum [[gnu::packed]] { ACK = 0, TEL = 1, AUTO = 2 } message_type;

typedef struct [[gnu::packed]] {
  /** Call sign */
  uint8_t header[16];

  /** Command Message Counter */
  uint8_t cmc;

  /** # of CMC */
  uint8_t n_cmc;

  /** Unique frame identifier */
  uint8_t frame_id;

  /** Message type */
  message_type type;

  /** Payload data */
  uint8_t data[215];
} frame_downlink_s;
