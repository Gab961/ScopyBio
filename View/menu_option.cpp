#include "menu_option.h"

menu_option::menu_option(QWidget *parent)
{
    setTitle("Options");

    m_gridOptions = new QGridLayout();

    m_notes = new QCheckBox("Show annotations", this);
    m_gridOptions->addWidget(m_notes, 0, 0);

    m_filter = new QCheckBox("Show filter", this);
    m_gridOptions->addWidget(m_filter, 1, 0);

    setLayout(m_gridOptions);
}
