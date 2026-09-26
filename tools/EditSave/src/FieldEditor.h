#pragma once

#include <QWidget>
#include <QVector>
#include "FieldDefs.h"
class SaveFile;
class QFormLayout;
class QCheckBox;

// ---------------------------------------------------------------------------
// Builds a form of spin boxes / line edits straight from the field manifest,
// grouped into collapsible sections. Reads values out of a SaveFile and writes
// edited ones back.
//
// Nothing is written on every keystroke: the editor keeps a working copy and
// only pushes values into the SaveFile when apply() is called, so a half-typed
// number can never land in the file.
// ---------------------------------------------------------------------------
class FieldEditor : public QWidget
{
    Q_OBJECT
public:
    explicit FieldEditor(QWidget *parent = nullptr);

    void setSave(SaveFile *save);
    void reload();                       // pull values back out of the save
    bool apply();                        // push edited values into the save
    bool hasPendingEdits() const;

signals:
    void dirtyChanged(bool dirty);

private:
    struct Slot {
        FieldDef        def;
        QWidget        *editor = nullptr;   // QSpinBox or QLineEdit
        QCheckBox      *lock   = nullptr;   // per-field "allow editing" override
    };

    void buildUi();
    QWidget *makeEditor(const FieldDef &def, QWidget **outEditor, QCheckBox **outLock);
    quint32  currentValue(const Slot &s) const;
    void     setCurrentValue(Slot &s, quint32 v);
    void     refreshLocks();

    SaveFile            *m_save = nullptr;
    QVector<Slot>        m_slots;
    QFormLayout         *m_form = nullptr;
    bool                 m_dirty = false;
};
