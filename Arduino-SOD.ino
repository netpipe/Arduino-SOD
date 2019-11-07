#include <SD.h>
#include <alloca.h>

#define SOD_ENABLE_NET_TRAIN
#include "sod.h"

#define MaxModelSize 16384
sod_cnn *pNet;
sod_realnet *realnet;
sod_realnet_model_handle *sodhandle;
File LoadedModel,Limage;

void * pModel;
void * pimage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialization done.");
  int rc=sod_realnet_create(&realnet);
if (SOD_OK == rc )
 {
   LoadedModel=SD.open("face.realnet");
   uint32_t Size=uint32_t(LoadedModel.size());
   if (Size<=MaxModelSize)
    {
      uint16_t  Size16=uint16_t(Size);
      pModel=alloca(Size16);
      if (pModel==NULL) {return;};
      LoadedModel.read(pModel,Size16);
      LoadedModel.close();
      rc = sod_realnet_load_model_from_mem(realnet,pModel, Size, sodhandle);
      Limage=SD.open("realnet_faces.jpg");
      Size16=uint16_t(Limage.size());
      pimage=alloca(Size16);
      if (pimage==NULL) {return;};
      Limage.read(pimage,Size16);
      Limage.close();
     // sod_img color = sod_img_load_color(zFile);
      sod_img img = sod_img_load_from_mem((unsigned char*)pimage,Size16,SOD_IMG_GRAYSCALE);
        unsigned char *zBlob = sod_image_to_blob(img);
      /* 
       * Bounding boxes array
       */
      sod_box *aBoxes;
      int nbox;
      /* 
        * Perform Real-Time detection on this blob
      */
       rc = sod_realnet_detect(realnet, zBlob, img.w, img.h, &aBoxes, &nbox);

    }
   
 }
 else
 {Serial.println("Error");}


}

void loop() {
  // put your main code here, to run repeatedly:

}




#include <stdio.h>
//#include "sod.h"
/*
 * Training log consumer callback that should be called
 * by the Realnet trainer to report training progress.
 */
void log_consumer_callback(const char *zText, size_t text_len, void *pUserdata)
{
  /* Simply redirect to stdout */
  puts(zText);
}

int train(const char *zTrainFile)
{
  /* Training instructions (i.e. where positive and negative samples
   * are located, tree minimal depth, max trees, model copyright notice and so on).
   * Pass a path or download one from https://pixlab.io/downloads
   */

   
//  const char *zTrainFile = argc > 1 ? argv[1] : "train.txt";
  /*
   * Relanet trainer handle
   */
  sod_realnet_trainer *pNett;
  int rc;
  /* Allocate a new Realnet Trainer handle */
  rc = sod_realnet_train_init(&pNett);
  if (rc != SOD_OK) return rc;
  /*
   * Install our training progress log consumer callback.
   */
  rc = sod_realnet_train_config(pNett, SOD_REALNET_TR_LOG_CALLBACK, log_consumer_callback, 0);
  if (rc != SOD_OK) return rc;
  /*
   * Where to store the output model.
   */
  rc = sod_realnet_train_config(pNett, SOD_REALNET_TR_OUTPUT_MODEL, "./pedestrian_detetcor.realnet");
  if (rc != SOD_OK) return rc;
  /*
   * Start the heavy training process on your CPU driven by
   * the Realnet instructions found on `zTrainFile`.
   */
  rc = sod_realnet_train_start(pNett, zTrainFile);
  /* Wait some days...*/
  sod_realnet_train_release(pNett);
  /* check the progress log and you should find
  * a working model on the path you specified earlier.
  */
  return rc;
}
