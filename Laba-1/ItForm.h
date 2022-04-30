#pragma once
template < class K, class D>
class ItForm
{
protected:
	TableForm <K, D>* table;
	ItForm(TableForm <K, D>* t);
	D& operator *() = 0;
	void operator ++() = 0;
	bool operator ==(const ItForm& it) = 0;
	bool operator !=(const ItForm& it) = 0;
};


