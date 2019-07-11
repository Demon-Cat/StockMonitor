#include "stockinfo.h"

StockInfo::StockInfo(const QString &strCode, QObject *parent) :
    QObject(parent),
    m_strCode(strCode)
{
    if (m_strCode == "000001")
    {
        m_strUrl = QString("http://hq.sinajs.cn/list=s_sh%1").arg(strCode);
    }
    else if (m_strCode.left(2) == QString("60"))
    {
        m_strUrl = QString("http://hq.sinajs.cn/list=s_sh%1").arg(strCode);
    }
    else if (m_strCode.left(2) == QString("00"))
    {
        m_strUrl = QString("http://hq.sinajs.cn/list=s_sz%1").arg(strCode);
    }
    else if (m_strCode.left(2) == QString("30"))
    {
        m_strUrl = QString("http://hq.sinajs.cn/list=s_sz%1").arg(strCode);
    }
}

QString StockInfo::code() const
{
    return m_strCode;
}

QUrl StockInfo::url() const
{
    return QUrl(m_strUrl);
}

void StockInfo::setName(const QString &name)
{
    m_strName = name;
}

QString StockInfo::name() const
{
    return m_strName;
}

void StockInfo::setValue(const qreal &value)
{
    m_value = value;
}

qreal StockInfo::value() const
{
    return m_value;
}

void StockInfo::setIncrease(const qreal &increase)
{
    m_increase = increase;
}

qreal StockInfo::increase() const
{
    return m_increase;
}

void StockInfo::setPercent(const qreal &percent)
{
    m_percent = percent;
}

qreal StockInfo::percent() const
{
    return m_percent;
}
