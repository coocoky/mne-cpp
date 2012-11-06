//=============================================================================================================
/**
* @file     fiffstreamthread.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti H�m�l�inen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains the implementation of the FiffStreamThread Class.
*
*/

#ifndef FIFFSTREAMTHREAD_H
#define FIFFSTREAMTHREAD_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../MNE/fiff/fiff_stream.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QThread>
#include <QTcpSocket>
#include <QMutex>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE MSERVER
//=============================================================================================================

namespace MSERVER
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================



class FiffStreamThread : public QThread
{
    Q_OBJECT

public:
    FiffStreamThread(quint8 id, int socketDescriptor, QObject *parent);

    void run();

    quint8 getID()
    {
        return m_iDataClientId;
    }

    QString getAlias()
    {
        return m_sDataClientAlias;
    }

    void read_command(FiffStream& p_FiffStreamIn, qint32 size);

//    void write_client_list(QTcpSocket& p_qTcpSocket);

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    quint8 m_iDataClientId;
    QString m_sDataClientAlias;

    int socketDescriptor;

    QMutex mutex;
    QByteArray m_qSendBlock;

//private slots: --> in Qt 5 not anymore declared as slot
    void getAndSendMeasurementInfo(qint32 ID, FiffInfo* p_pFiffInfo);

//private slots: --> in Qt 5 not anymore declared as slot
//    void readFiffStreamServerInstruction(quint8 id, quint8 instruction);

};

} // NAMESPACE

#endif //FIFFSTREAMTHREAD_H