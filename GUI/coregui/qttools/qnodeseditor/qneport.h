/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef QNEPORT_H
#define QNEPORT_H

#include <QGraphicsPathItem>
#include <QString>
class QNEBlock;
class QNEConnection;
class ISampleView;

class QNEPort : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 1 };

    enum { NamePort = 1, TypePort = 2 };

    //! in/out ports with the same type can be connected together
    enum PortType
    {
        Default,
        Interference,
        ParticleFactory,
        FormFactor
    };

    enum PortDirection
    {
        Input,
        Output
    };

//    QNEPort(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
//    QNEPort(QGraphicsItem *parent = 0, const QString &name=QString("unnamed"), bool isOutput=false);
    QNEPort(QGraphicsItem *parent = 0, const QString &name=QString("unnamed"), PortDirection direction = Input, PortType port_type = Default);

	~QNEPort();

//    void setNEBlock(QNEBlock*);
    void setNEBlock(ISampleView*);

	void setName(const QString &n);
	void setIsOutput(bool o);
	int radius();
	bool isOutput();
	QVector<QNEConnection*>& connections();
	void setPortFlags(int);

    const QString& portName() const { return m_name; }
//	int portFlags() const { return m_portFlags; }

	int type() const { return Type; }

//    QNEBlock* block() const;
    ISampleView* block() const;

	quint64 ptr();
	void setPtr(quint64);

	bool isConnected(QNEPort*);

    static QColor getPortTypeColor(QNEPort::PortType port_type);

    PortType getPortType() const { return m_port_type; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString m_name;
//    bool m_isOutput;
    PortDirection m_direction;
    PortType m_port_type;

    QColor m_color;
    int m_radius;
    int m_margin;
//    QNEBlock *m_block;
    ISampleView *m_block;
	QGraphicsTextItem *label;
	QVector<QNEConnection*> m_connections;
	int m_portFlags;
	quint64 m_ptr;

};

#endif // QNEPORT_H
