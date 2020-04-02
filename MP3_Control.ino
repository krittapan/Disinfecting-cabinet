void myPlayer(uint8_t Track)
{
  myMP3Player.play(Track);
  while(myMP3Player.readType() != DFPlayerPlayFinished && myMP3Player.readCurrentFileNumber() == Track)
  {
    delay(0);
  }
}
void MP3DetailChack(uint8_t type, int value)
{
  switch (type) {
    case TimeOut:
      DebugSerial.println(F("Time Out!"));
      break;
    case WrongStack:
      DebugSerial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      DebugSerial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      DebugSerial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      DebugSerial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      DebugSerial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      DebugSerial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      DebugSerial.print(F("Number:"));
      DebugSerial.print(value);
      DebugSerial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      DebugSerial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          DebugSerial.println(F("Card not found"));
          break;
        case Sleeping:
          DebugSerial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          DebugSerial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          DebugSerial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          DebugSerial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          DebugSerial.println(F("Cannot Find File"));
          break;
        case Advertise:
          DebugSerial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}