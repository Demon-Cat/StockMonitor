#ifndef STOCKINFO_H
#define STOCKINFO_H

#include <QObject>
#include <QUrl>

class StockInfo : public QObject
{
    Q_OBJECT
public:
    explicit StockInfo(const QString &strCode, QObject *parent = nullptr);

    QString code() const;
    QUrl url() const;

    void setName(const QString &name);
    QString name() const;
    void setValue(const qreal &value);
    qreal value() const;
    void setIncrease(const qreal &increase);
    qreal increase() const;
    void setPercent(const qreal &percent);
    qreal percent() const;

signals:

public slots:

private:
    QString m_strCode;
    QString m_strUrl;
    QString m_strName;
    qreal m_value = 0;
    qreal m_increase = 0;
    qreal m_percent = 0;
};

#endif // STOCKINFO_H
