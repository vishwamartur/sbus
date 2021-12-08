/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "sbus/sbus.h"

/* SBUS object, reading SBUS */
bfs::SbusRx sbus_rx;
/* SBUS object, writing SBUS */
bfs::SbusTx sbus_tx;

int main() {
  /* Serial to display data */
  Serial.begin(115200);
  while(!Serial) {}
  /* RX Config */
  Serial.print("Initializing SBUS receiver...");
  while (!sbus_rx.Init(&Serial2)) {}
  Serial.println("done.");
  /* TX Config */
  sbus_tx.Init(&Serial2);
  while (1) {
    if (sbus_rx.Read()) {
      /* Print the SBUS data */
      Serial.print(sbus_rx.lost_frame());
      Serial.print("\t");
      Serial.print(sbus_rx.failsafe());
      Serial.print("\t");
      std::array<int16_t, bfs::SbusRx::NUM_CH> data = sbus_rx.ch();
      for (std::size_t i = 0; i < data.size(); i++) {
        Serial.print(data[i]);
        Serial.print("\t");
      }
      Serial.print(sbus_rx.ch17());
      Serial.print("\t");
      Serial.println(sbus_rx.ch18());
      /* Write the SBUS data */
      sbus_tx.ch(data);
      sbus_tx.Write();
    }
  }
}


