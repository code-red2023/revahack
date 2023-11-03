import serial
import pyodbc
import time

# Define your MSSQL server and database connection details
server = 'LAPTOP-6ROHRJ0P\SQLEXPRESS'
database = 'linkesh'
username = 'sa'
password = 'manager'

# Establish a connection to the MSSQL database
conn_str = f'DRIVER={{ODBC Driver 17 for SQL Server}};SERVER={server};DATABASE={database};UID={username};PWD={password};Trusted_Connection=yes;'
conn = pyodbc.connect(conn_str)
cursor = conn.cursor()
print("cursor")

# Define the serial port name and baud rate for your ESP32
serial_port = 'COM3'  # Change this to your ESP32's serial port
baud_rate =115200   # Adjust to match your ESP32 configuration

# Initialize the serial port communication
ser = serial.Serial(serial_port, baud_rate)
# Thresholds for decision-making
water_threshold = 4  # mm
soil_moisture_threshold = 80  # Percentage
temperature_threshold = 24  # Celsius
humidity_threshold = 60  # Percentage



try:
  while True:
        # Read a line of data from the serial port
    data = ser.readline().decode('utf-8').strip().lstrip(".")
    value_list =list( data.split(","))
    print(data)
    print(data[5])
    #query = "INSERT INTO DATA (TimeStamp, temp, hum, weather_description, rain_fall, rain_predict, water_to_drip, irrigation) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
    
    rain_prediction = int(data[5])
    rainfall = int(data[4])
    rainfall_time = float(data[0])
    temperature = float(data[1])
    humidity = int(data[2])
    current_time = time.time()
    print(rain_prediction)
    print(rainfall)
    print(rainfall_time)
    print(temperature)
    print(humidity)

    

    # Decision-making
    if rain_prediction >0.50:
        print(rain_prediction)
        if rainfall < water_threshold:
            print(rainfall)
            if current_time > rainfall_time:
                print(current_time)
                if soil_moisture < soil_moisture_threshold:
                    print(soil_moisture)
                    if temperature > temperature_threshold and humidity < humidity_threshold:
                        value_list.append("10")
                        value_list.append("yes")

                        print("Initiating irrigation...")
                        
                        # Implement irrigation control logic here
                    else:
                        value_list.append("10")
                        value_list.append("no")
                        print("No irrigation needed.")
                else:
                    print("No irrigation needed.")
                    value_list.append("10")
                    value_list.append("no")
            else:
                    print("Rainfall detected. No irrigation needed.")
                    value_list.append("10")
                    
                    value_list.append("no")
              
    
          
        
    
   


    

    # Insert the data into the database
    value_list.append("10")
    value_list.append("yes")
    
    
    query = "INSERT INTO DATA (TimeStamp, temp, hum, weather_description, rain_fall, rain_predict, water_to_drip, irrigation) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"

    # Use the cursor to execute the query and provide the value_list as parameters
    cursor.execute(query, value_list)
    conn.commit()
  
            

        

        # Print the data for verification
    print(f'Received and stored: {data}')

except KeyboardInterrupt:
    print("Script terminated by user.")
finally:
    conn.close()
    ser.close()
