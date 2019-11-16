#include <SD.h>
#include <alloca.h>
#include "sod.h"

 const char *zFile ="realnet_faces.jpg";


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
  sod_realnet *pNet; /* Realnet handle */
  int i,rc;
  /*
   * Allocate a new RealNet handle */
  rc = sod_realnet_create(&pNet);
  if (rc != SOD_OK) return ;
  /* 
   * Register and load a RealNet model.
   * You can train your own RealNet model on your CPU using the training interfaces [sod_realnet_train_start()]
   * or download pre-trained models like this one from https://pixlab.io/downloads
   */
  rc = sod_realnet_load_model_from_disk(pNet, "./face.realnet.sod", 0);
  if (rc != SOD_OK) return ;
  /* Load the target image in grayscale colorspace */
  sod_img img = sod_img_load_grayscale(zFile);
  if (img.data == 0) {
    puts("Cannot load image");
    return ;
  }
  /* Load a full color copy of the target image so we draw rose boxes
   * Note that drawing on grayscale images is also supported.
   */
  sod_img color = sod_img_load_color(zFile);
  /*
   * convert the grayscale image to blob.
   */
  unsigned char *zBlob = sod_image_to_blob(img);
  /* 
   * Bounding boxes array
   */
  sod_box *aBoxes;
  int nbox;
  /* 
   * Perform Real-Time detection on this blob
   */
  rc = sod_realnet_detect(pNet, zBlob, img.w, img.h, &aBoxes, &nbox);
  if (rc != SOD_OK) return ;
  /* Consume result */
  printf("%d potential face(s) were detected..\n", nbox);
  for (i = 0; i < nbox; i++) {
    /* Ignore low score detection */
    if (aBoxes[i].score < 5.0) continue;
    /* Report current object */
    printf("(%s) x:%d y:%d w:%d h:%d prob:%f\n", aBoxes[i].zName, aBoxes[i].x, aBoxes[i].y, aBoxes[i].w, aBoxes[i].h, aBoxes[i].score);
    /* Draw a rose box on the target coordinates */
    sod_image_draw_bbox_width(color, aBoxes[i], 3, 255., 0, 225.);
    //sod_image_draw_circle(color, aBoxes[i].x + (aBoxes[i].w / 2), aBoxes[i].y + (aBoxes[i].h / 2), aBoxes[i].w, 255., 0, 225.);
  }
  /* Save the detection result */
  sod_img_save_as_png(color,"out.png");
  /* cleanup */
  sod_free_image(img);
  sod_free_image(color);
  sod_image_free_blob(zBlob);
  sod_realnet_destroy(pNet);




}

void loop() {
  // put your main code here, to run repeatedly:

}
