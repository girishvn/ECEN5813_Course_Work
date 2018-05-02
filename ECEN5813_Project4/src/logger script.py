#Dictionary to map the log event enums
logEventId = {'00': "SYSTEM_ID", '01': "SYSTEM_VERSION", '02': "LOGGER_INITIALIZED", '03': "GPIO_INITIALIZED", '04': "SYSTEM_HALTED",
              '05': "INFO", '06': "WARNING", '07': "ERROR", '08': "PROFILING_STARTED", '09': "PROFILING_RESULT", '0A': "DATA_RECEIVED",
              '0B': "DATA_ANALYSIS_STARTED", '0C': "DATA_ALPHA_COUNT", '0D': "DATA_NUMERIC_COUNT", '0E': "DATA_PUNCTUATION_COUNT", '0F': "DATA_MISC_COUNT",
              '10': "DATA_ANALYSIS_COMPLETED", '11': "HEARTBEAT", '12': "CORE_DUMP"}

#Dictionary to map the module ID enums
fileID = {'00': "CIRCBUF", '01': "CONVERSION", '02': "DMA", '03': "GPIO", '04': "LOGGER",
            '05': "LOGGERQUEUE", '06': "MAIN", '07': "MEMORY", '08': "NORDIC", '09': "PROFILING", '0A': "PROJECTFOUR",
            '0B': "SPI", '0C': "TIMER", '0D': "UART", '0E': "????????????", '0F': "??????????",
            '10': "??????????", '11': "????????", '12': "??????????????"}

#Begin processing the binary log into meaningful data#
with open("outputfile.txt",'w') as ofh: #File to write the translated data
    with open("binarylogger.txt") as f: #Parse through the binary logger text generated from the Kl25Z
        content = f.readlines() #Read line by line
        content = [x.strip() for x in content] #Remove whitespace characters like `\n` at the end of each line
        for items in content: #Translate item by item
            eventId = items[:2] #Get the eventID
            print(eventId)

            moduleId = items[2:4] #Get the moduleID
            print(moduleId)

            timeStamp = items[4:12] #Get the timeStamp
            print(timeStamp)

            payLoadByteCnt = items[12:14] #Get the Payload Byte Count
            print(payLoadByteCnt)

            payLoadMsgEndPos = 14+int(payLoadByteCnt, 16) #Calculate the end byte of the payload message
            payLoadMsg = items[14:payLoadMsgEndPos] #Get the Payload Message
            print(payLoadMsg)

            checkSum = items[payLoadMsgEndPos:(payLoadMsgEndPos+8)] #Get the CheckSum
            print(int(checkSum, 16))

            #Perform Check Sum to make sure data is correct before printing the log#
            MsgVal = 0
            for c in payLoadMsg:
                MsgVal += int(ord(c)) #Add each character's ASCII value in the Payload message
            print(MsgVal)
            checkSum2 = int(eventId, 16) + int(moduleId, 16) + int(timeStamp, 16) + int(payLoadByteCnt, 16) + MsgVal #Calculate the checkSum
            print(checkSum2)

            if(int(checkSum, 16) == checkSum2): #If checksum matches, log data into outputfile
                log = '[' + fileID.get(moduleId) + ']: ' + str(int(timeStamp, 16)) + ' - [' + logEventId.get(eventId) + '] - ' + payLoadMsg
            else: #data was corrupted
                log = "Corrupted Data"
            ofh.write(log)
f.close()