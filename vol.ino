const int analogInputPin = A0;  // 模拟输入引脚
const float smoothingFactor = 0.05;  // 平滑系数
const float voltageOffset = 0.041;  // 修正偏差值
const int measurementCount = 50;  // 测量次数

float filteredValue = 0.0;  // 过滤后的数值

void setup() {
  Serial.begin(9600);  // 初始化串口通信
}

void loop() {
  // 执行测量并累加测量值
  float accumulatedVoltage = 0.0;
  for (int i = 0; i < measurementCount; i++) {
    int sensorValue = analogRead(analogInputPin);
    accumulatedVoltage += (sensorValue * (5.0 / 1023.0)) - voltageOffset;
    delay(1);  // 等待一小段时间，可根据实际情况调整
  }

  // 计算平均电压值
  float averageVoltage = accumulatedVoltage / measurementCount;

  // 使用递推平均滤波器进行滤波
  filteredValue = (smoothingFactor * averageVoltage) + ((1 - smoothingFactor) * filteredValue);

  // 输出滤波后的结果
  Serial.print("Filtered Voltage: ");
  Serial.println(filteredValue, 4);

  // 检测测量结束条件
  if (abs(filteredValue - averageVoltage) < 0.01) {  // 根据实际情况调整判定条件
    // 测量成功，输出最终结果
    Serial.print("Final: ");
    Serial.print(filteredValue, 3);
    Serial.println("V");
    
    // 其他操作
    // ...
    
    while (true) {}  // 停止程序运行，可根据实际情况调整
  }
}
