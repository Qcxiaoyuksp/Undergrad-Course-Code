package com.mayinlong.service;

import java.util.List;

import com.mayinlong.dao.BookDao;
import com.mayinlong.entity.BookDB;
import com.mayinlong.utils.PageTool;

public class BookService {
	
	private BookDao bookDao=new BookDao();
	public PageTool<BookDB> listByPage(String currentPage, String pageSize,String word){
		return bookDao.list(currentPage, pageSize,word);
	}
	public List<BookDB> list(String bookName){
		return bookDao.list(bookName);
	}
	public Integer addBook(BookDB bookDB) {
		return bookDao.addBook(bookDB);
	}
	
	public Integer updBook(BookDB bookDB) {
		return bookDao.updBook(bookDB);
	}
	public int delBook(String bid) {
		return bookDao.delBook(bid);
	}

}
