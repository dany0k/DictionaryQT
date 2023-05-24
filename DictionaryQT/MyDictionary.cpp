#include "MyDictionary.h"

void Dictionary::addWordsFromFile(const QString& filename)
{
    filePath = filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << filename;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList words = line.split(" ", Qt::SkipEmptyParts);
        for (const QString& word : words)
        {
            if (!word.isEmpty())
                m_dictionary[word]++;
        }
    }

    file.close();
}

void Dictionary::saveToFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QJsonObject jsonDict;
    for (auto it = m_dictionary.constBegin(); it != m_dictionary.constEnd(); ++it)
    {
        jsonDict[it.key()] = it.value();
    }

    QJsonDocument jsonDoc(jsonDict);
    file.write(jsonDoc.toJson());
    file.close();
}

void Dictionary::loadFromFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:" << filename;
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonDict = jsonDoc.object();

    m_dictionary.clear();
    for (auto it = jsonDict.constBegin(); it != jsonDict.constEnd(); ++it)
    {
        QString word = it.key();
        int count = it.value().toInt();
        m_dictionary[word] = count;
    }
    file.close();
}

QMap<QString, int> Dictionary::getDict() {
    return m_dictionary;
}
