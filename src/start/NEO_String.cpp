 
#include <NEO_String.h>
#include <NEO_Types.h>

size_t NEO::String::Length(const char* src)
{
	size_t i=0;
	while(*src--)
		i++;
	return i;
}
int NEO::String::Cpy(char* dest, const char* src)
{
	int n = 0;
	while (*src)
	{
		*dest++ = *src++;
		n++;
	}
	*dest = '\0';
	return n;
}
int NEO::String::Comp(const char *p1, const char *p2)
{
  int i = 0;
  int neq = 0;
  while(p1[i] != '\0' && p2[i] != '\0')
  {
    if(p1[i] != p2[i])
    {
      neq = 1;
      break;
    }
    i++;
  }
  if( (p1[i] == '\0' && p2[i] != '\0') || (p1[i] != '\0' && p2[i] == '\0') )
    neq = 1;

  return neq;
}
char* NEO::String::Cat(char *dest, const char *src)
{
  int di = NEO::String::Length(dest);
  int si = 0;
  while (src[si])
    dest[di++] = src[si++];
  
  dest[di] = '\0';

  return dest;
}
bool NEO::String::IsUpper(char c)
{
  return (c >= 'A' && c <= 'Z') ? true : false;
}

bool NEO::String::IsLower(char c)
{
  return (c >= 'a' && c <= 'z') ? true : false;
}

bool NEO::String::IsDigit(char c)
{
  return (c >= '0' && c <= '9') ? true : false;
}
