#pragma once
template < class K, class D>
class ItForm
{
protected:
	TableForm <K, D>* table;
	ItForm(TableForm <K, D>* t);
	virtual D& operator *() = 0;
	virtual void operator ++() = 0;
	virtual bool operator ==(const ItForm& it) = 0;
	virtual bool operator !=(const ItForm& it) = 0;
};


