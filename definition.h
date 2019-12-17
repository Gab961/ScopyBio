#ifndef DEFINITION_H
#define DEFINITION_H
#define separator  =
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}
#endif // DEFINITION_H
