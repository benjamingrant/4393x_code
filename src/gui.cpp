#include "gui.h"
#include "main.h"
#include "display/lvgl.h"

static lv_res_t btn_click_action(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  uint8_t id = lv_obj_get_free_num(btn);
  char mytext[64];

  sprintf(mytext, "Button %d is released\n", id);
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void gui(void) {

 /*Create a title label*/
 lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
 lv_label_set_text(label, "Select a Button");
 lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

 /*Create a normal button*/
 static lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
 lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
 lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
 lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
 lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the button*/
 label = lv_label_create(btn1, NULL);
 lv_label_set_text(label, "Choice 1");

 /*Copy the button and set toggled state. (The release action is copied too)*/
 static lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
 lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
 // lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
 lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
 lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the toggled button*/
 label = lv_label_create(btn2, NULL);
 lv_label_set_text(label, "Choice 2");

 /*Copy the button and set inactive state.*/
 static lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
 lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 10);
 //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
 lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
 lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

 /*Add a label to the inactive button*/
 label = lv_label_create(btn3, NULL);
 lv_label_set_text(label, "Choice 3");
}
