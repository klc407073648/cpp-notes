package src;

BoolQueryBuilder boolQueryBuilder = QueryBuilders.boolQuery();
// 过滤
boolQueryBuilder.filter(QueryBuilders.termQuery("isDelete", 0));
if (id != null) {
    boolQueryBuilder.filter(QueryBuilders.termQuery("id", id));
}
if (notId != null) {
    boolQueryBuilder.mustNot(QueryBuilders.termQuery("id", notId));
}
if (userId != null) {
    boolQueryBuilder.filter(QueryBuilders.termQuery("userId", userId));
}
// 必须包含所有标签
if (CollectionUtils.isNotEmpty(tagList)) {
    for (String tag : tagList) {
boolQueryBuilder.filter(QueryBuilders.termQuery("tags", tag));
    }
}
// 包含任何一个标签即可
if (CollectionUtils.isNotEmpty(orTagList)) {
    BoolQueryBuilder orTagBoolQueryBuilder = QueryBuilders.boolQuery();
    for (String tag : orTagList) {
orTagBoolQueryBuilder.should(QueryBuilders.termQuery("tags", tag));
    }
    orTagBoolQueryBuilder.minimumShouldMatch(1);
    boolQueryBuilder.filter(orTagBoolQueryBuilder);
}
// 按关键词检索
if (StringUtils.isNotBlank(searchText)) {
    boolQueryBuilder.should(QueryBuilders.matchQuery("title", searchText));
    boolQueryBuilder.should(QueryBuilders.matchQuery("content", searchText));
    boolQueryBuilder.minimumShouldMatch(1);
}
// 按标题检索
if (StringUtils.isNotBlank(title)) {
    boolQueryBuilder.should(QueryBuilders.matchQuery("title", title));
    boolQueryBuilder.minimumShouldMatch(1);
}
// 按内容检索
if (StringUtils.isNotBlank(content)) {
    boolQueryBuilder.should(QueryBuilders.matchQuery("content", content));
    boolQueryBuilder.minimumShouldMatch(1);
}
// 排序
SortBuilder<?> sortBuilder = SortBuilders.scoreSort();
if (StringUtils.isNotBlank(sortField)) {
    sortBuilder = SortBuilders.fieldSort(sortField);
    sortBuilder.order(CommonConstant.SORT_ORDER_ASC.equals(sortOrder) ? SortOrder.ASC : SortOrder.DESC);
}
// 分页
PageRequest pageRequest = PageRequest.of((int) current, (int) pageSize);
// 构造查询
NativeSearchQuery searchQuery = new NativeSearchQueryBuilder().withQuery(boolQueryBuilder)
.withPageable(pageRequest).withSorts(sortBuilder).build();
SearchHits<PostEsDTO> searchHits = elasticsearchRestTemplate.search(searchQuery, PostEsDTO.class);