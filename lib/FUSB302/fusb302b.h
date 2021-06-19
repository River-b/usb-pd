/*
 * PD Buddy Firmware Library - USB Power Delivery for everyone
 * Copyright 2017-2018 Clayton G. Hobbs
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PDB_FUSB302B_H
#define PDB_FUSB302B_H

#include "fusb302_defines.h"
#include "pd.h"
#include "pdb_msg.h"

class FUSB302 {
public:
  typedef bool (*I2CFunc)(const uint8_t addr, const uint8_t size, uint8_t *buf);
  FUSB302(uint8_t address, I2CFunc read, I2CFunc write);

  void fusb_send_message(const pd_msg *msg) const;
  bool fusb_rx_pending() const;
  /*
   * Read a USB Power Delivery message from the FUSB302B
   */
  uint8_t fusb_read_message(pd_msg *msg) const;

  /*
   * Tell the FUSB302B to send a hard reset signal
   */
  void fusb_send_hardrst() const;

  /*
   * Read the FUSB302B status and interrupt flags into *status
   */
  bool fusb_get_status(fusb_status *status) const;

  /*
   * Read the FUSB302B BC_LVL as an enum fusb_typec_current
   */
  enum fusb_typec_current fusb_get_typec_current() const;

  /*
   * Initialization routine for the FUSB302B
   */
  bool fusb_setup() const;

  /*
   * Reset the FUSB302B
   */
  void fusb_reset() const;

  bool fusb_read_id() const;

private:
  const uint8_t DeviceAddress; // I2C address for this device
  // I2C bus access functions, should return true if command worked
  // Function to write data to the FUSB302
  const I2CFunc I2CWrite;

  // Function to read data from the FUSB302
  const I2CFunc I2CRead;
  uint8_t       fusb_read_byte(const uint8_t addr);
  bool          fusb_write_byte(const uint8_t addr, const uint8_t byte);
};

#endif /* PDB_FUSB302B_H */
