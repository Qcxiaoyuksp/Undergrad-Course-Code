package com.dao;

import com.entity.JiangzuoyuyueEntity;
import com.baomidou.mybatisplus.mapper.BaseMapper;
import java.util.List;
import java.util.Map;
import com.baomidou.mybatisplus.mapper.Wrapper;
import com.baomidou.mybatisplus.plugins.pagination.Pagination;

import org.apache.ibatis.annotations.Param;
import com.entity.vo.JiangzuoyuyueVO;
import com.entity.view.JiangzuoyuyueView;


/**
 * 讲座预约
 * 
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
public interface JiangzuoyuyueDao extends BaseMapper<JiangzuoyuyueEntity> {
	
	List<JiangzuoyuyueVO> selectListVO(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
	
	JiangzuoyuyueVO selectVO(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
	
	List<JiangzuoyuyueView> selectListView(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);

	List<JiangzuoyuyueView> selectListView(Pagination page,@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
	
	JiangzuoyuyueView selectView(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
	

    List<Map<String, Object>> selectValue(@Param("params") Map<String, Object> params,@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);

    List<Map<String, Object>> selectTimeStatValue(@Param("params") Map<String, Object> params,@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
    
    List<Map<String, Object>> selectGroup(@Param("params") Map<String, Object> params,@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
}
