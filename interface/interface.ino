void receiveData();

void setup()
{
  Serial.begin(9600); // Starts the serial communication
}

void loop()
{
  receiveData();
  // if (Serial.available() > 0)
  // {
  //   char data = Serial.read();
  //   char str[2];
  //   str[0] = data;
  //   str[1] = '\0';
  //   Serial.print(str);
  // }
}
#define DATA_MAX_SIZE = 3
static byte data[DATA_MAX_SIZE];
void receiveData()
{
  static char endMarker = 0xf5; // message separator
  char receivedChar;            // read char from serial port
  byte ndx = 0;                 // current index of data buffer
  // clean data buffer
  memset(data, 0, sizeof(data));
  // read while we have data available and we are
  // still receiving the same message.
  while (Serial.available() > 0)
  {
    receivedChar = Serial.read();
    if (receivedChar == endMarker)
    {
      data[ndx] = '\0'; // end current message
      return;
    }
    // looks like a valid message char, so append it and
    // increment our index
    data[ndx] = receivedChar;
    ndx++;
    // if the message is larger than our max size then
    // stop receiving and clear the data buffer. this will
    // most likely cause the next part of the message
    // to be truncated as well, but hopefully when you
    // parse the message, you'll be able to tell that it's
    // not a valid message.
    if (ndx >= DATA_MAX_SIZE)
    {
      break;
    }
  }
  // no more available bytes to read from serial and we
  // did not receive the separato. it's an incomplete message!
  Serial.println("error: incomplete message");
  Serial.println(data);
  memset(data, 0, sizeof(data));
}