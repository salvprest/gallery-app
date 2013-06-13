/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Nicolas d'Offay <nicolas.doffay@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "command-line-parser.h"

#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

CommandLineParser::CommandLineParser(const QHash<QString, QSize>& form_factors)
    : m_startupTimer(false),
      m_isFullscreen(false),
      m_isPortrait(false),
      m_picturesDir(QDir(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))),
      m_logImageLoading(false),
      m_formFactors(form_factors),
      m_formFactor("desktop")
{
}

/*!
 * @brief CommandLineParser::processArguments parsers our input commandline args and sets attributes accordingly.
 * @param QStringList of commandline args to parse and set attributes.
 * @return false if invalid parameter is input or -h/--help is called.
 */
bool CommandLineParser::processArguments(const QStringList& args)
{
    bool valid_args = true;

    for (int i = 1; i < args.count(); ++i)
    {
        QString value = (i + 1 < args.count() ? args[i + 1] : "");

        if (args[i] == "--help" || args[i] == "-h") {
            usage();
            return false;
        }
        else if (args[i] == "--landscape") {
            m_isPortrait = false;
        }
        else if (args[i] == "--portrait") {
            m_isPortrait = true;
        }
        else if (args[i] == "--fullscreen") {
            m_isFullscreen = true;
        }
        else if (args[i] == "--startup-timer") {
            m_startupTimer = true;
        }
        else if (args[i] == "--log-image-loading") {
            m_logImageLoading = true;
        }
        else {
            QString form_factor = args[i].mid(2); // minus initial "--"

            if (args[i].startsWith("--") && m_formFactors.keys().contains(form_factor)) {
                m_formFactor = form_factor;
            }
            else if (args[i].startsWith("--desktop_file_hint")) {
                // ignore this command line switch, hybris uses it to get application info
            }
            else if (i == args.count() - 1 && QDir(args[i]).exists()) {
                m_picturesDir = QDir(args[i]);
            }
            else {
                valid_args = !invalidArg(args[i]);
            }
        }
    }

    return valid_args;
}

/*!
 * @brief CommandLineParser::usage() prints out our form factors.
 */
void CommandLineParser::usage()
{
    QTextStream out(stdout);
    out << "Usage: gallery [options] [pictures_dir]" << endl;
    out << "Options:" << endl;
    out << "  --landscape\trun in landscape orientation (default)" << endl;
    out << "  --portrait\trun in portrait orientation" << endl;
    out << "  --fullscreen\trun fullscreen" << endl;

    foreach (const QString& form_factor, m_formFactors.keys()) {
        out << "  --" << form_factor << "\trun in " << form_factor << " form factor" << endl;
    }

    out << "  --startup-timer\n\t\tdebug-print startup time" << endl;
    out << "  --log-image-loading\n\t\tlog image loading" << endl;
    out << "pictures_dir defaults to ~/Pictures, and must exist prior to running gallery" << endl;
}

/*!
 * @brief CommandLineParser::invalidArg() if an invalid argument is contained in our QStringList.
 * @return returns true.
 */
bool CommandLineParser::invalidArg(QString arg)
{
    QTextStream(stderr) << "Invalid argument '" << arg << "'" << endl;
    usage();

    return true;
}