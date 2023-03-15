

void beginEEPROM(){
   EEPROM.begin(EEPROM_SIZE);

   // Write an ID at first time
   //eepromWrite(EEPROM_ADDR_ID,1);
   deviceId = DEVICE_ID_BASE + eepromRead(EEPROM_ADDR_ID);

}

int eepromRead(int adr){
    return EEPROM.read(adr);
}

void eepromWrite(int addr, uint8_t val){
   EEPROM.write(addr, val);
   EEPROM.commit();
}
