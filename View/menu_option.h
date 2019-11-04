#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>


class menu_option: public QGroupBox
{
    Q_OBJECT

    public:
        menu_option(QWidget *parent);

    private:
        QGridLayout *m_gridOptions;

        QCheckBox *m_notes;
        QCheckBox *m_filter;
};
