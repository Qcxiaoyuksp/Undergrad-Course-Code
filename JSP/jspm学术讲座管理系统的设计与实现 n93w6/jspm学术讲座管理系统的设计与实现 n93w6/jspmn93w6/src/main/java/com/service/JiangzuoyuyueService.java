package com.service;

import com.baomidou.mybatisplus.mapper.Wrapper;
import com.baomidou.mybatisplus.service.IService;
import com.utils.PageUtils;
import com.entity.JiangzuoyuyueEntity;
import java.util.List;
import java.util.Map;
import com.entity.vo.JiangzuoyuyueVO;
import org.apache.ibatis.annotations.Param;
import com.entity.view.JiangzuoyuyueView;


/**
 * 讲座预约
 *
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
public interface JiangzuoyuyueService extends IService<JiangzuoyuyueEntity> {

    PageUtils queryPage(Map<String, Object> params);
    
   	List<JiangzuoyuyueVO> selectListVO(Wrapper<JiangzuoyuyueEntity> wrapper);
   	
   	JiangzuoyuyueVO selectVO(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
   	
   	List<JiangzuoyuyueView> selectListView(Wrapper<JiangzuoyuyueEntity> wrapper);
   	
   	JiangzuoyuyueView selectView(@Param("ew") Wrapper<JiangzuoyuyueEntity> wrapper);
   	
   	PageUtils queryPage(Map<String, Object> params,Wrapper<JiangzuoyuyueEntity> wrapper);
   	

    List<Map<String, Object>> selectValue(Map<String, Object> params,Wrapper<JiangzuoyuyueEntity> wrapper);

    List<Map<String, Object>> selectTimeStatValue(Map<String, Object> params,Wrapper<JiangzuoyuyueEntity> wrapper);
    
    List<Map<String, Object>> selectGroup(Map<String, Object> params,Wrapper<JiangzuoyuyueEntity> wrapper);
}

