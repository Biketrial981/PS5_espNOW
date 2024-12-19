// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      //Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
      ctl->setColorLED(0, 255, 0);
      ctl->setPlayerLEDs(led & 0x0f);
      // Additionally, you can get certain gamepad properties like:
      // Model, VID, PID, BTAddr, flags, etc.
      ControllerProperties properties = ctl->getProperties();
      //Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      break;
      }
    }

    if (!foundEmptySlot) {
      //Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      //Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
      myControllers[i] = nullptr;
      foundController = true;
      break;
    }
  }

    if (!foundController) {
      //Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

// ========= SEE CONTROLLER VALUES IN SERIAL MONITOR ========= //

void dumpGamepad(ControllerPtr ctl) {
  //Serial.printf(
  //"idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
  //"misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
  //ctl->index(),        // Controller Index
  //ctl->dpad(),         // D-pad
  //ctl->buttons(),      // bitmask of pressed buttons
  //ctl->axisX(),        // (-511 - 512) left X Axis
  //ctl->axisY(),        // (-511 - 512) left Y axis
  //ctl->axisRX(),       // (-511 - 512) right X axis
  //ctl->axisRY(),       // (-511 - 512) right Y axis
  //ctl->brake(),        // (0 - 1023): brake button
  //ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
  //ctl->miscButtons(),  // bitmask of pressed "misc" buttons
  //ctl->gyroX(),        // Gyro X
  //ctl->gyroY(),        // Gyro Y
  //ctl->gyroZ(),        // Gyro Z
  //ctl->accelX(),       // Accelerometer X
  //ctl->accelY(),       // Accelerometer Y
  //ctl->accelZ()        // Accelerometer Z
  //);
}

void processControllers() {
  for (auto myController : myControllers) {
    if (myController && myController->isConnected() && myController->hasData()) {
      if (myController->isGamepad()) {
         processGamepad(myController);
      }
      else {
        //Serial.println("Unsupported controller");
      }
    }
  }
}

void registrar_clientes() {
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }
  /// register 4 peer
  memcpy(peerInfo.peer_addr, broadcastAddress4, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    //Serial.println("Failed to add peer");
    return;
  }    
}