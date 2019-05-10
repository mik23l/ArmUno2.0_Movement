/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    server_interface.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "server_interface.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


// *****************************************************************************

/**
  @Function
    void ServerInitialize();

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
void ServerInitialize(){
    // Open the UART1 channel for message transfer
    PLIB_USART_Disable (USART_ID_1);
    //Use PLIB Fucntions
    
        uint32_t clockSource;
        
        /* Initialize the USART based on configuration settings */
    PLIB_USART_InitializeModeGeneral(USART_ID_1,
            false,  /*Auto baud*/
            false,  /*LoopBack mode*/
            false,  /*Auto wakeup on start*/
            false,  /*IRDA mode*/
            false);  /*Stop In Idle mode*/
    
        /* Set the line control mode */
    PLIB_USART_LineControlModeSelect(USART_ID_1, USART_8N1);
    
        /* We set the receive interrupt mode to receive an interrupt whenever FIFO
       is not empty */
    PLIB_USART_InitializeOperation(USART_ID_1,
            USART_RECEIVE_FIFO_ONE_CHAR,
            USART_TRANSMIT_FIFO_IDLE,
            USART_ENABLE_TX_RX_USED);
    
        /* Get the USART clock source value*/
    clockSource = SYS_CLK_PeripheralFrequencyGet ( CLK_BUS_PERIPHERAL_1 );
    
    /* Set the baud rate and enable the USART */
    PLIB_USART_BaudSetAndEnable(USART_ID_1,
            clockSource,
            BAUDRATE_SERVER);  /*Desired Baud rate value*/
    
    /* Clear the interrupts to be on the safer side*/
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    
        /* Enable the error interrupt source */
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_ERROR);

    /* Enable the Receive interrupt source */
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_RECEIVE);
    
    SYS_INT_VectorPrioritySet(INT_VECTOR_UART1, INT_PRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_UART1, INT_SUBPRIORITY_LEVEL0);
    
    PLIB_USART_TransmitterEnable (USART_ID_1);
    PLIB_USART_ReceiverEnable (USART_ID_1);
    PLIB_USART_Enable (USART_ID_1);
}

// *****************************************************************************

/**
  @Function
    UARTMessage ReadResponse();

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
UARTMessage ReadResponse(){
    UARTMessage result = UARTReceiveFromQueue(GetJsonQueue);
    return result;
}

// *****************************************************************************

/**
  @Function
    void GetResponse(BaseType_t *pxHigherPriorityTaskWoken);

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
void GetResponse(BaseType_t *pxHigherPriorityTaskWoken){
    dbgOutputLoc(BEFORE_UART_READ);
    UARTMessage Response = PLIB_USART_ReceiverByteReceive(USART_ID_1);
    UARTQueueSendToBackFromISR(Response, GetJsonQueue, pxHigherPriorityTaskWoken);
    dbgOutputLoc(AFTER_UART_READ);
}

// *****************************************************************************

/**
  @Function
    void SendRequest(BaseType_t *pxHigherPriorityTaskWoken);

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
void SendRequest(BaseType_t *pxHigherPriorityTaskWoken){
    dbgOutputLoc(BEFORE_UART_WRITE);
    UARTMessage Request = UARTQueueReceiveFromISR(PutJsonQueue, pxHigherPriorityTaskWoken);
    if(Request != EMPTY_REQUEST)
    {
        PLIB_USART_TransmitterByteSend(USART_ID_1, Request);
    }
    else
    {
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
        SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
    }
    dbgOutputLoc(AFTER_UART_WRITE);
}

// *****************************************************************************

/**
  @Function
    WriteRequestHelper(char* Message, size_t Length)

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
WriteRequestHelper(char* Message, size_t Length)
{
    int i;
    for(i = 0; i != Length; ++i)
    {
        UARTQueueSendToBack(Message[i], PutJsonQueue);
        SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    }
}

// *****************************************************************************

/**
  @Function
    void WriteGet(DocumentName document)

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
void WriteGet(DocumentName document)
{
    static char Request[256];
    switch(document)
    {
        case Sensor:
        {
            strcpy(Request, "GET /sensor HTTP/1.1\r\nHost: 192.168.0.10:80\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 2\r\n\r\n{}");
        }
        break;
        case Rover:
        {
            strcpy(Request, "GET /rover HTTP/1.1\r\nHost: 192.168.0.10:80\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 2\r\n\r\n{}");
        }
        break;
        case Arms:
        {
            strcpy(Request, "GET /arms HTTP/1.1\r\nHost: 192.168.0.10:80\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 2\r\n\r\n{}");
        }
        break;
        case Station:
        {
            strcpy(Request, "GET /station HTTP/1.1\r\nHost: 192.168.0.10:80\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 2\r\n\r\n{}");
        }
        break;
        case DataLog:
        {
            strcpy(Request, "GET /datalog HTTP/1.1\r\nHost: 192.168.0.10:80\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 2\r\n\r\n{}");
        }
        break;
        default:
        {
            dbgOutputError(ERROR_DOC_NAME);
        }
        break;
    }
    size_t Length = strlen(Request);
    WriteRequestHelper(Request, Length);
}

// *****************************************************************************

/**
  @Function
    WritePut(DocumentName document, const Package *pack)

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
WritePut(DocumentName document, const Package *pack)
{
    static char Message[1024];
    static char data[512];
    switch(document)
    {
        case Sensor:
        {
            sprintf(Message, "PUT /sensor HTTP/1.1\r\nHost: 192.168.0.10\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:%d\r\n\r\n%s", strlen(data), data);

        }
        break;
        case Rover:
        {
            sprintf(Message, "PUT /rover HTTP/1.1\r\nHost: 192.168.0.10\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:%d\r\n\r\n%s", strlen(data), data);
        }
        break;
        case Arms:
        {
            int CheckSum = pack -> ArmStatus;
            sprintf(data, "{\"name\":\"arms\", \"Status\":%d, \"CheckSum\": %d, \"SN\":%d}", pack -> ArmStatus, CheckSum, pack -> SequenceNumber);
            sprintf(Message, "PUT /arms HTTP/1.1\r\nHost: 192.168.0.10\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:%d\r\n\r\n%s", strlen(data), data);

        }
        break;
        case Station:
        {
            sprintf(Message, "PUT /station HTTP/1.1\r\nHost: 192.168.0.10\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:%d\r\n\r\n%s", strlen(data), data);
        }
        break;
        case DataLog:
        {
            int CheckSum = pack -> RequestSent + pack -> CorrectResponse + pack -> MissedResponse + pack -> BadResponse;
            sprintf(data, "{\"name\":\"armsdatalog\", \"RequestSent\": %d, \"GoodRequest\": %d, \"BadRequest\": %d,\"MissedRequest\":%d, \"CheckSum\": %d}", pack -> RequestSent, pack -> CorrectResponse, pack -> BadResponse, pack -> MissedResponse, CheckSum);
            sprintf(Message, "PUT /armsdatalog HTTP/1.1\r\nHost: 192.168.0.10\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length:%d\r\n\r\n%s", strlen(data), data);
        }
        break;
        default:
        {
            dbgOutputError(ERROR_DOC_NAME);
        }
        break;
    }
    size_t Length = strlen(Message);
    WriteRequestHelper(Message, Length);
}

// *****************************************************************************

/**
  @Function
    void WriteRequest(RequestType type, DocumentName document, const Package *pack);

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
 */
void WriteRequest(RequestType type, DocumentName document, const Package *pack){
    switch(type)
    {
        case GET:
        {
            WriteGet(document);
        }
        break;
        case PUT:
        {
            WritePut(document, pack);
        }
    }
}


/* *****************************************************************************
 End of File
 */
