#ifndef QWT_MML_ENTITY_TABLE_H
#define QWT_MML_ENTITY_TABLE_H

#include <qwt_global.h>

#include <qstring.h>

class QWT_EXPORT QwtMMLEntityTable
{
public:
    struct Spec
    {
        const char *name;
        const char *value;
    };

    QString entities() const;
    const Spec *search( const QString &value, const Spec *from = nullptr ) const;
};

#endif





