package books.utils;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class DateUtils {
	
	private static SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
	

	public static String dateToString(Date date) {
		return sdf.format(date);
	}

	public static Date stringToDate(String dt) {
		try {
			return sdf.parse(dt);
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	//日期增加
	public static Date dateAdd(Date date, int i) {
		Calendar calendar = new GregorianCalendar();
		calendar.setTime(date);
		calendar.add(Calendar.DATE,i); //把日期往后增加一天,整数  往后推,负数往前移动
		date=calendar.getTime(); //这个时间就是日期往后推一天的结果
		return date;		
	}
}
