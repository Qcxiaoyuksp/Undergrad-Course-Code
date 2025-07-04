package books.service;

import java.util.List;

import books.dao.TypeDao;
import books.entity.TypeDB;
import books.utils.PageTool;

/**
 * 图书类别
 * @author Administrator
 *
 */
public class TypeService {

	private TypeDao typeDao = new TypeDao(); //type的实体类
	
	//分页显示
	public PageTool<TypeDB> listByPage(String currentPage, String pageSize){
		return typeDao.listByPage(currentPage, pageSize);
	}
	
	//条件查询
	public List<TypeDB> list(String tid,String typeName) {
		return typeDao.list(tid, typeName);
	}
	
	//添加类型
	public Integer addType(String typeName) {
		return typeDao.addType(typeName);
	}
	
	//修改类别
	public Integer updType(TypeDB typeDB) {
		return typeDao.updType(typeDB);
	}
	
	//删除类别
	public int delType(Integer tid) {
		return typeDao.delType(tid);
	}
}
