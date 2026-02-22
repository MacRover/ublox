//==============================================================================
// Copyright (c) 2012, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================

#ifndef UBLOX_SERIALIZATION_CHECKSUM_HPP
#define UBLOX_SERIALIZATION_CHECKSUM_HPP

#include <cstdint>

namespace ublox {

/**
 * @brief calculate the checksum of a u-blox_message
 * @param data the start of the u-blox message
 * @param data the size of the u-blox message
 * @param ck_a the checksum a output
 * @param ck_b the checksum b output
 */
static inline void calculateChecksum(const uint8_t *data,
                                     uint32_t size,
                                     uint8_t &ck_a,
                                     uint8_t &ck_b) {
  ck_a = 0; ck_b = 0;
  for(uint32_t i = 0; i < size; ++i)
  {
    ck_a = ck_a + data[i];
    ck_b = ck_b + ck_a;
  }
}

/**
 * @brief calculate the checksum of a u-blox_message.
 * @param data the start of the u-blox message
 * @param data the size of the u-blox message
 * @param checksum the checksum output
 * @return the checksum
 */
static inline uint16_t calculateChecksum(const uint8_t *data,
                                         uint32_t size,
                                         uint16_t &checksum) {
  uint8_t *byte = reinterpret_cast<uint8_t *>(&checksum);
  calculateChecksum(data, size, byte[0], byte[1]);
  return checksum;
}


static inline uint32_t Crc24Quick(uint32_t Crc, uint32_t Size, const uint8_t *Buffer) // sourcer32@gmail.com
{
  static const uint32_t crctab[] = { // Nibble lookup for Qualcomm CRC-24Q
    0x00000000,0x01864CFB,0x038AD50D,0x020C99F6,0x0793E6E1,0x0615AA1A,0x041933EC,0x059F7F17,
    0x0FA18139,0x0E27CDC2,0x0C2B5434,0x0DAD18CF,0x083267D8,0x09B42B23,0x0BB8B2D5,0x0A3EFE2E };
 
  ssize_t i = 0;
  while(Size--)
  {
    Crc ^= (uint32_t)Buffer[i++] << 16; // Apply byte
    // Process 8-bits, 4 at a time, or 2 rounds
    Crc = (Crc << 4) ^ crctab[(Crc >> 20) & 0x0F];
    Crc = (Crc << 4) ^ crctab[(Crc >> 20) & 0x0F];
  }
 
  return(Crc & 0xFFFFFF); // Mask to 24-bit, as above optimized for 32-bit
}

}  // namespace ublox

#endif  // UBLOX_SERIALIZATION_CHECKSUM_HPP
