#pragma once

#include <QObject>
#include <QString>

// ---------------------------------------------------------------------------
// Runtime language switching.
//
// English is the source language, so it needs no translator at all - the
// tr() strings in the C++ are already English and Qt shows them verbatim.
// Russian is a compiled editsave_ru.qm loaded from a QTranslator.
//
// Two things make this awkward and are handled here rather than in each call
// site:
//
//  1. Installing a translator does not re-evaluate tr() on widgets that
//     already exist, and there is no reliable way to make every widget in the
//     app re-run its own tr() calls without a retranslateUi() slot in all
//     seven of them. The window is therefore rebuilt on change, which is
//     correct by construction rather than correct by inspection.
//
//  2. A QTranslator must be removed and destroyed before the next one is
//     installed. Reassigning the pointer without uninstalling leaves the
//     previous catalogue in Qt's list and frees memory it still points at.
class Translator : public QObject
{
    Q_OBJECT
public:
    static Translator &instance();

    // Loads editsave_<code>.qm. Safe to call repeatedly; a no-op if the code
    // is already active. Emits languageChanged() only when the effective
    // language actually changed, so a failed load does not trigger a rebuild.
    void applyLanguage(const QString &code);

    // Code currently active, which may differ from the requested one if the
    // .qm was missing.
    QString current() const { return m_code; }

    // Directory searched for the .qm files, for diagnostics.
    static QString searchPath();

signals:
    void languageChanged(const QString &code);

private:
    Translator() = default;

    QString m_code = QStringLiteral("en");
};
