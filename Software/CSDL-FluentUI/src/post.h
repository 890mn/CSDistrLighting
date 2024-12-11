#include <QObject>
#include <QString>

class MarqueeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString marqueeText READ marqueeText WRITE setMarqueeText NOTIFY marqueeTextChanged)

public:
    MarqueeManager(QObject *parent = nullptr) : QObject(parent), m_marqueeText("初始公告内容11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111") {}

    QString marqueeText() const {
        return m_marqueeText;
    }

    void setMarqueeText(const QString &text) {
        if (m_marqueeText != text) {
            m_marqueeText = text;
            emit marqueeTextChanged();
        }
    }

signals:
    void marqueeTextChanged();

private:
    QString m_marqueeText;
};
