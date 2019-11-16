#include <SD.h>


#include "sod.h"


void log_consumer_callback(const char *zText, size_t text_len, void *pUserdata)
{
  /* Simply redirect to stdout */
  Serial.print(zText);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

//SD card must be initialized before call sod files functions
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialization done.");
  /* Training instructions (i.e. where positive and negative samples
   * are located, tree minimal depth, max trees, model copyright notice and so on).
   * Pass a path or download one from https://pixlab.io/downloads
   */
  const char *zTrainFile = "train.txt";
  /*
   * Relanet trainer handle 
   */
  sod_realnet_trainer *pNet;
  int rc;
  /* Allocate a new Realnet Trainer handle */
  rc = sod_realnet_train_init(&pNet);
  if (rc != SOD_OK) 
   {
    Serial.print("Error allocate model");
    return;
   }
  /*
   * Install our training progress log consumer callback.
   */
  rc = sod_realnet_train_config(pNet, SOD_REALNET_TR_LOG_CALLBACK, log_consumer_callback, 0);
  if (rc != SOD_OK) 
   {
    Serial.print("Error in installing training progress");
    return;
   }
  /*
   * Where to store the output model.
   */
  rc = sod_realnet_train_config(pNet, SOD_REALNET_TR_OUTPUT_MODEL, "./pedestrian_detetcor.realnet");
  if (rc != SOD_OK) 
   {
    Serial.print("Error in cnfigure training model");
    return;
   }
  /*
   * Start the heavy training process on your CPU driven by
   * the Realnet instructions found on `zTrainFile`.
   */
  rc = sod_realnet_train_start(pNet, zTrainFile);
  /* Wait some days...*/
  sod_realnet_train_release(pNet);
  /* check the progress log and you should find
  * a working model on the path you specified earlier.
  */


}

void loop() {
  // put your main code here, to run repeatedly:

}
