module.exports = 
{
    lineNumbers: true, // 行号
    externalLinks: {
        target: '_blank', rel: 'noopener noreferrer'  // 外部链接
    },
    anchor: { permalink: false }, // markdown-it-anchor 
    toc: {
        includeLevel: [1, 2, 3, 4]  // markdown-it-toc 生成markdown目录层次
    }
}