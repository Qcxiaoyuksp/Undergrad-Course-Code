package com.mayinlong.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import com.mayinlong.entity.ProblemDB;
import com.mayinlong.utils.C3p0Tool;
import com.mayinlong.utils.PageTool;

public class ProblemDao {

	QueryRunner queryRunner = new QueryRunner(C3p0Tool.getDataSource());
	//开启驼峰自动转换
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	/**
	 * 列表 分页
	 * @return
	 */
	public PageTool<ProblemDB> list(String currentPage, String pageSize, String word, Integer order, Integer uid){
		try {
			StringBuffer listSql = new StringBuffer("select p.*,name,account");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer(" from t_problem p left join t_user u on p.uid = u.uid where 1 = 1");
			List<Object> params = new ArrayList<>();
			if (uid != null) {
				sql.append(" and p.uid = ?");
				params.add(uid);
			}
			if (word != null && !word.isEmpty()) {
				sql.append(" and title like '%" + word + "%'");
				sql.append(" or page like '%" + word + "%'");
				sql.append(" or content like '%" + word + "%'");
				sql.append(" or name like '%" + word + "%'");
				sql.append(" or account like '%" + word + "%'");
			}
			
			if (order != null && order == 1) {
				sql.append(" order by time desc");
			}
			//获取总记录数
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>(),params.toArray());
			//初始化分页工具
			PageTool<ProblemDB> pageTools = new PageTool<ProblemDB>(total.intValue(), currentPage, pageSize);
			sql.append(" limit ?,?");
			params.add(pageTools.getStartIndex());
			params.add(pageTools.getPageSize());
			//当前页的数据		
			 List<ProblemDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<ProblemDB>(ProblemDB.class, processor),params.toArray());
			 pageTools.setRows(list);
			 System.out.println(pageTools);
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return new PageTool<ProblemDB>(0, currentPage, pageSize);
	}
	
	
	/**
	 * 添加问题
	 * @param ProblemDB
	 * @return
	 */
	public Integer addProblem(ProblemDB problemDB) {
		String sql = "insert into t_problem (uid,title,page,content,link,status,time) values (?,?,?,?,?,?,?)";
		Object[] params = {problemDB.getUid(),problemDB.getTitle(), problemDB.getPage(),problemDB.getContent(),problemDB.getLink(),problemDB.getStatus(),problemDB.getTime()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 修改问题
	 * @return
	 */
	public Integer updProblem(ProblemDB ProblemDB) {
		String sql = "update t_problem set status = ? where pid = ?";
		Object[] params = {ProblemDB.getStatus(),ProblemDB.getPid()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	/**
	 * 删除问题
	 * @return 
	 */
	public Integer delBook(String pid) {
		String sql = "delete from t_problem where pid = ?";
		Object[] params = {pid};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
}
