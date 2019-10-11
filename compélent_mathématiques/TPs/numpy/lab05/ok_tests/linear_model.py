test = {
  'name': 'linear_model',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> w = np.array([-3, 2, 0.5, -1]);
          >>> X = np.array([[4, -5,  2],
          ...               [5,  3, -3],
          ...               [5,  2,  1],
          ...               [8,  6,  9],
          ...               [5, -6,  2]]);
          >>> 
          >>> linear_model(X, w)
          array([ 0.5, 11.5,  7. ,  7. ,  2. ])
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
