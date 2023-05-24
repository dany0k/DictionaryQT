#ifndef MYDICTIONARY_H
#define MYDICTIONARY_H

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QTextStream>

class Dictionary
{
public:
    void addWordsFromFile(const QString& filename);
    void saveToFile(const QString& filename);
    void loadFromFile(const QString& filename);
    QMap<QString, int> getDict();
private:
    QMap<QString, int> m_dictionary;
    QString filePath;
};

#endif // MYDICTIONARY_H
