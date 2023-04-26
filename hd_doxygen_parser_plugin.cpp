/**
 * @file hd_doxygen_parser_plugin.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief doxygen parser plugin for header_docu
 * @details parse doxygen header
 * @version 1.0.0
 * @date 2023-04-25
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#include "hd_doxygen_parser_plugin.h"

Hd_doxygen_parser_plugin::Hd_doxygen_parser_plugin(QObject *parent)
{
    Q_UNUSED(parent);
    // qDebug() << "Plugin Constructor";
}

Hd_doxygen_parser_plugin::~Hd_doxygen_parser_plugin()
{
    //qDebug() << "Plugin Deconstructed";
}

void Hd_doxygen_parser_plugin::test(QString name)
{
    qInfo() << "Test from " << PLUGIN_SHORTNAME << " Plugin: " << name;
}

QString Hd_doxygen_parser_plugin::getName()
{
    return PLUGIN_SHORTNAME;
}

QString Hd_doxygen_parser_plugin::getVersion()
{
    return PLUGIN_NAME + "-v" + PLUGIN_VERSION;
}

void Hd_doxygen_parser_plugin::parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile)
{
    // qDebug() << "Hd_doxygen_parser_plugin::parseFile: " << pathToFile;

    QFile file(pathToFile);
    QString searchBegin = QRegularExpression::escape("/**");
    QRegularExpression reBegin(searchBegin);
    QString searchEnd = QRegularExpression::escape("*/");
    QRegularExpression reEnd(searchEnd);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString line;
    bool isComment = false;

    QString matchedKey;

    while (in.readLineInto(&line)) {
        QRegularExpressionMatch matchStart = reBegin.match(line);
        QRegularExpressionMatch matchEnd = reEnd.match(line);
        if (matchStart.hasMatch()) {
            isComment = true;
            continue;
        }
        if (matchEnd.hasMatch()) {
            isComment = false;
            break;
        }
        if (isComment) {
            if (line.isEmpty()) {
                // todo
            } else {
                for (auto [key, val] : mapParseKeys.asKeyValueRange()) {
                    QRegularExpression searchKey(key, QRegularExpression::CaseInsensitiveOption);
                    QRegularExpressionMatch matchSearchStr = searchKey.match(line);
                    if (matchSearchStr.hasMatch()) {
                        //qInfo() << "matched: " << matchSearchStr.captured(0) << " " << matchSearchStr.captured(1);
                        matchedKey = key;
                    }
                }
                line.replace(matchedKey.toLower(), "");
                line.replace("* @", "");
                line.replace("*", "");
                QString newLine = line.trimmed();
                if (newLine.length() != 0) {
                    mapParseKeys[matchedKey].append(newLine + "\n");
                    //qInfo() << "### match:\n" << newLine;
                }
            }
        } else {
            break;
        }
    }

    file.close();
}

void Hd_doxygen_parser_plugin::writeFile(QMap<QString, QString> mapParseKeys,
                                         QMap<QString, QString> mapFileAttribs,
                                         QString pathToFile)
{}
