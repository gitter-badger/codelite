#ifndef ZJSONNODE_H
#define ZJSONNODE_H

#include <wx/string.h>
#include <wx/variant.h>
#include <wx/filename.h>
#include <wx/arrstr.h>
#include <wx/gdicmn.h>
#include "codelite_exports.h"
#include <map>
#include "cJSON.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CL JSONElement
{
protected:
    cJSON * _json;
    int     _type;
    wxString _name;

    // Values
    wxVariant _value;
    
public:
    typedef std::map<wxString, wxString> wxStringMap_t;

public:
    JSONElement(cJSON *json);
    JSONElement(const wxString &name, const wxVariant& val, int type);
    
    virtual ~JSONElement() {}

    // Setters
    ////////////////////////////////////////////////
    void setName(const wxString& _name) {
        this->_name = _name;
    }
    void setType(int _type) {
        this->_type = _type;
    }
    int getType() const {
        return _type;
    }
    const wxString& getName() const {
        return _name;
    }
    const wxVariant& getValue() const {
        return _value;
    }
    void setValue(const wxVariant& _value) {
        this->_value = _value;
    }
    // Readers
    ////////////////////////////////////////////////
    JSONElement   namedObject(const wxString& name) const ;
    bool          hasNamedObject(const wxString &name) const;
    bool          toBool()           const ;
    wxString      toString()         const ;
    wxArrayString toArrayString()    const ;
    JSONElement   arrayItem(int pos) const ;
    bool          isNull()           const ;
    bool          isBool()           const ;
    bool          isString()         const ;
    wxString      format()           const ;
    int           arraySize()        const ;
    int           toInt(int defaultVal = -1) const ;
    size_t        toSize_t(size_t defaultVal = -1) const ;
    double        toDouble(double defaultVal = -1.0) const;
    wxSize        toSize() const;
    wxPoint       toPoint() const;
    JSONElement::wxStringMap_t toStringMap() const;
    
    
    // Writers
    ////////////////////////////////////////////////
    /**
     * @brief create new named object and append it to this json element
     * @return the newly created object
     */
    static JSONElement createObject(const wxString &name = wxT(""));
    /**
     * @brief create new named array and append it to this json element
     * @return the newly created array
     */
    static JSONElement createArray(const wxString &name = wxT(""));

    /**
     * @brief append new element to this json element
     */
    void append(const JSONElement& element);
    
    /**
     * @brief add string property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, const wxString &value);
    JSONElement& addProperty(const wxString& name, const wxChar* value);
    
    /**
     * @brief add int property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, int value);
    JSONElement& addProperty(const wxString &name, size_t value);

    /**
     * @brief add boolean property to a JSON object
     */
    JSONElement& addProperty(const wxString &name, bool value);
    
    JSONElement& addProperty(const wxString &name, const wxSize& sz);
    JSONElement& addProperty(const wxString &name, const wxPoint& pt);
    
    /**
     * @brief add wxArrayString property 
     */
    JSONElement& addProperty(const wxString &name, const wxArrayString &arr);
    
    JSONElement& addProperty(const wxString &name, const JSONElement::wxStringMap_t& stringMap);
    /**
     * @brief delete property by name
     */
    void removeProperty(const wxString &name);
    
    //////////////////////////////////////////////////
    // Array operations
    //////////////////////////////////////////////////

    /**
     * @brief append new number
     * @return the newly added property
     */
    void arrayAppend(const JSONElement& element);
    void arrayAppend(const wxString &value);

    bool isOk() const {
        return _json != NULL;
    }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CL JSONRoot
{
    cJSON *_json;
    wxString _errorString;

public:
    JSONRoot(int type);
    JSONRoot(const wxString& text);
    JSONRoot(const wxFileName& filename);
    virtual ~JSONRoot();
    
    void save(const wxFileName &fn) const;
    wxString errorString() const;
    bool isOk() const {
        return _json != NULL;
    }

    JSONElement toElement() const;

    void clear();

private:
    // Make this class not copyable
    JSONRoot(const JSONRoot& src);
    JSONRoot& operator=(const JSONRoot& src);
};


#endif // ZJSONNODE_H
