package books.service;

import java.sql.SQLException;

import books.dao.HistoryDao;
import books.entity.HistoryDB;
import books.utils.PageTool;

public class HistoryService {
	
	private HistoryDao historyDao = new HistoryDao();

	public PageTool<HistoryDB> listByPage(String currentPage, String pageSize, Integer uid, Integer status){
		return historyDao.listByPage(currentPage, pageSize, uid, status);
	}
	
	public Integer updHistory(HistoryDB historyDB) throws SQLException {
		return historyDao.updHistory(historyDB);
	}
}
