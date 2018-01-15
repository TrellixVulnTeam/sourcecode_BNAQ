/*!
 * @file   ISqliteService.h
 * @author kongxilong
 * @param  Email: hzkongxilong@corp.netease.com
 * @param  Copyright(C) 2016 
 * @date   2016/06/05
 * @brief  ���ݿ����ӿ�
 */

#pragma  once

#include "..\core\ISingleton.h"
#include "DBModel.h"


//ֻ�Ǽ̳����е�����Ľӿ�
class ISqliteService : public ISingletonBase
{

public:
    //�������ݿ⼰����
	virtual BOOL CreanteDB() = 0;
	virtual BOOL QueryAllCompany(std::list<Company>& companys) = 0;
    virtual BOOL IsComanyExist(const CString& company) = 0;
	virtual BOOL NewComany(const CString& company) = 0;
	virtual BOOL RemoveComany(const CString& company) = 0;
	virtual BOOL QueryAllDepartment(std::list<Department>& departs)= 0;
	virtual BOOL IsDepartmentExist(const int64_t& companyid,const CString& depart) = 0;
	virtual BOOL NewDepartment(const int64_t& companyid,const CString& depart)= 0;
	virtual BOOL RemoveDepartment(const int64_t& companyid,const CString& depart)= 0;
	virtual BOOL QueryAllEmploye(std::list<Employe>& employes) = 0;
	virtual BOOL IsEmployExist(const int64_t& companyid,const int64_t& departid,const CString& employ) = 0;
	virtual BOOL NewEmploy(const int64_t& companyid,const int64_t& departid,const CString& employ) = 0;
	virtual BOOL RemoveEmploy(const int64_t& companyid,const int64_t& departid,const CString& employ) = 0;
	virtual BOOL FindComidByComName(const CString& name, int64_t& id) = 0;
	virtual BOOL FindDepartmentIDByDepartmentName(const int64_t& comid,const CString& name, int64_t& departid) = 0;
};

